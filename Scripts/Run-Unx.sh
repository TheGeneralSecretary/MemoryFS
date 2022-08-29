#!/usr/bin/env bash

pushd ../build/linux-x86-Debug
exec ./MemoryFS/MemoryFS
popd
