#!/bin/bash

set -e -x

shopt -s expand_aliases

source $HOME/osbook/devenv/buildenv.sh

make
