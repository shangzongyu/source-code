package main

import (
	"bytes"
	"context"
	"encoding/binary"
	"fmt"
	"log"
	"os"
	"os/signal"
	"syscall"

	bpf "github.com/aquasecurity/libbpfgo"
)

type Event struct {
	Pid       uint32
	Ret       uint32
	HiddenPid [8]byte
	Comm      [16]byte
}

type Config struct {
	ToHidePid [8]byte
}

func parseEvent(data []byte) (*Event, error) {
	var event Event
	err := binary.Read(bytes.NewBuffer(data), binary.LittleEndian, &event)
	if err != nil {
		return nil, err
	}
	return &event, nil
}

func main() {
	var err error
	defer func() {
		if err != nil {
			log.Fatalf("%+v", err)
		}
	}()

	bpfModule, err := bpf.NewModuleFromFile("main.bpf.o")
	if err != nil {
		return
	}
	defer bpfModule.Close()

	pid := os.Getpid()
	log.Printf("pid: %d\n", pid)
	toHidePid := [8]byte{}
	bs := []byte(fmt.Sprintf("%d", pid))
	for i, v := range bs {
		toHidePid[i] = v
	}
	config := Config{ToHidePid: toHidePid}
	if err = bpfModule.InitGlobalVariable("configs", config); err != nil {
		return
	}

	if err = bpfModule.BPFLoadObject(); err != nil {
		return
	}
	progIter := bpfModule.Iterator()
	for {
		prog := progIter.NextProgram()
		if prog == nil {
			break
		}
		_, err = prog.AttachGeneric()
		if err != nil {
			return
		}
	}
	log.Println("tracing...")
	eventsChannel := make(chan []byte)
	lostChannel := make(chan uint64)
	pb, err := bpfModule.InitPerfBuf("events", eventsChannel, lostChannel, 1024)
	if err != nil {
		return
	}
    log.Printf("will hide pid %d", pid)
	ctx, stop := signal.NotifyContext(context.Background(), os.Interrupt, syscall.SIGTERM)

	pb.Start()
	defer func() {
		pb.Stop()
		pb.Close()
		stop()
	}()

loop:
	for {
		select {
		case data := <-eventsChannel:
			event, e := parseEvent(data)
			if e != nil {
				err = e
				return
			} else {
				log.Printf("pid: %d, comm: %s, hidden_pid: %s ret: %d",
					event.Pid, event.Comm, event.HiddenPid, event.Ret)
			}
		case n := <-lostChannel:
			log.Printf("lost %d events", n)
		case <-ctx.Done():
			break loop
		}
	}
	log.Println("bye bye~")
}
