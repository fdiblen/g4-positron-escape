FROM fdiblen/gentoo:hep

MAINTAINER fdiblen

ENV container docker
ENV LC_ALL en_US.UTF-8

ENV DISPLAY :0
ENV EDITOR vim
ENV TERM xterm-256color
ENV SHELL /bin/bash

ADD code /home/positronEscape
WORKDIR /home/positronEscape

COPY g4-wrapper.sh /usr/local/bin/g4-wrapper.sh

ENTRYPOINT ["/usr/local/bin/g4-wrapper.sh"]
CMD []
