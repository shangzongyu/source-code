package main

import (
	"fmt"
	"net/url"

	"github.com/gocolly/colly"
)

var domain2Collector = map[string]*colly.Collector{}
var nc *nats.Conn
var maxDepth = 10
var natsURL = "nats://localhost:4222"

func factory(urlStr string) *colly.Collector {
	u, _ := url.Parse(urlStr)
	return domain2Collector[u.Host]
}

func initABCDECollector() *colly.Collector {
	c := colly.NewCollector(
		colly.AllowedDomains("www.abcdefg.com"),
		colly.MaxDepth(maxDepth),
	)

	c.OnResponse(func(resp *colly.Response) {
		// 做一些爬完之后的善后工作
		// 比如页面已爬完的确认存进 MySQL
	})

	c.OnHTML("a[href]", func(e *colly.HTMLElement) {
		// 基本的反爬虫策略
		link := e.Attr("href")
		time.Sleep(time.Second * 2)

		// 正则 match 列表页的话，就 visit
		if listRegex.Match([]byte(link)) {
			c.Visit(e.Request.AbsoluteURL(link))
		}
		// 正则 match 落地页的话，就发消息队列
		if detailRegex.Match([]byte(link)) {
			err = nc.Publish("tasks", []byte(link))
			nc.Flush()
		}
	})
	return c
}

func initHIJKLCollector() *colly.Collector {
	c := colly.NewCollector(
		colly.AllowedDomains("www.hijklmn.com"),
		colly.MaxDepth(maxDepth),
	)

	c.OnHTML("a[href]", func(e *colly.HTMLElement) {
	})

	return c
}

func init() {
	domain2Collector["www.abcdefg.com"] = initABCDECollector()
	domain2Collector["www.hijklmn.com"] = initHIJKLCollector()
	var err error
	nc, err = nats.Connect(natsURL)
	if err != nil {os.Exit(1)}
}

func main() {
	urls := []string{"https://www.abcdefg.com", "https://www.hijklmn.com"}
	for _, url := range urls {
		instance := factory(url)
		instance.Visit(url)
	}
}