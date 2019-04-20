#!/usr/bin/env bash

script/locate.sh 2>script/.log
script/extract.sh <resourses/jit10.dump 2>&1 >resourses/.code