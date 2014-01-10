fastflow
========

LK optical flow with FAST features


## vagrant build

```vagrant up``` in the directory then develop as normal

initially : 6044164 bytes used
finally : 10210312 bytes used

image size : ~4.0 GB

time taken : 1751.991s

## docker build

```docker build -t <name> .``` to build a container
```docker run -v `pwd`:/vagrant -t <name> -i /bin/bash``` to run the container with similar mounting to vagrant

initially : 6047860 bytes used
finally : 10422016 bytes used

image size : ~4.2 GB

time taken : 2715.812


