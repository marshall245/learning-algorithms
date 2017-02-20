#! /bin/bash

gcc -o bin/test_run test_sorts.c test_utils.c sorts.c heaps.c
chmod +x bin/test_run