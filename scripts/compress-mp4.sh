#!/usr/bin/env python3
import runpy
import sys
from pathlib import Path

sys.argv = [sys.argv[0], "mp4", *sys.argv[1:]]
runpy.run_path(str(Path(__file__).with_name("compress-media.py")), run_name="__main__")
