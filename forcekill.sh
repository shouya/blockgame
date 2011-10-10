#!/bin/bash

kill -9 `ps | grep blockgame | awk '{print $1}'` 
