#!/bin/bash

MOUNT_POINT=/mnt/udisk

if [ -d "${MOUNT_POINT}/autotest" ]; then
      board=`cat /proc/device-tree/model`
      echo $board > /dev/console

      cp -raf ${MOUNT_POINT}/autotest/$board  /tmp

      /tmp/$board/test.sh
fi
