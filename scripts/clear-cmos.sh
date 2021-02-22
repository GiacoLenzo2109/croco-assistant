#!/bin/bash
modprobe nvram 
dd if=/dev/zero of=/dev/nvram
