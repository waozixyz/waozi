+++
title = "Exploring 9front on my RPi4"
date = 2022-04-22
description = "My experience to setting up and customizing 9front, a fork of Plan 9, on a Raspberry Pi 4."

[taxonomies]
tags = ["9front", "Plan 9", "Raspberry Pi", "operating systems", "customization", "system configuration", "keyboard layout", "time synchronization", "terminal", "rio window manager", "werc", "web server", "DIY computing", "alternative OS", "system administration"]
categories = ["Technology & How-to"]

[extra]
image = "/images/writings/glenda_space.jpg"
image_alt = "Glenda Space"
read_time = "2 min read"
+++

# Exploring [9front](http://9fs.net/) on my Raspberry Pi 4

- profile file = $home/lib/profile
- riostart file = $home/rc/bin/riostart

## Add permanent keyboard layout change

Simply add this line with the kbmap you want to use to your profile file in the terminal case:

> cat /sys/lib/kbmap/dvorak > /dev/kbmap

## Sync time automatically at start

Just add this line to the profile file in the terminal case:

> aux/timesync -n pool.ntp.org

[source](https://web.archive.org/web/20230321233918/https://clueelf.wordpress.com/2018/06/29/clocks-time-ntp-plan9-9front/)

## Fix "buggy" spawned terminal

In your riostart file ($profile/bin/rc) simply remove the following line:

> ; ~ $#console 0 || window -scroll console

and replace it with:

> window -scroll

## Fixing the background

First of all, make sure to follow this [tutorial](http://www.ftrv.se/14) to get the theme patch on rio working.

(If by accident you run the patch twice then you will get a lot of errors and you need to reset the hg tree and get the original rio files again)

Once you got themes working go to:

> cd /sys/src/cmd/rio

> acme rio.c

and simply follow the short guide to my rio background fix:

> [rio-background-fix](/rio-background-fix.txt)

For some reason the background is buggy until the rio window is resized, so the "bug fix" I made is just a stripped down version of the resized function in rio.c and I put it in redraw to execute it once since I did not know where else to put it to make sure it is run once at the start.

After the code has been fixed make sure to run mk and if no bugs were encountered run:

> mk install

## werc

This [tutorial](http://docs.a-b.xyz/rc-httpd-werc.html) is great. I was just confused on how to start the listener. Running this line fixed the problem:

> aux/listen

To get the web server working and I also struggled at first to comprehend how to use the sites directory.

Simply make a folder with your local ip such as 192.168.0.2 and you can use it immediately with werc if everything is set up correctly.

You can also set up a loopback to use other local folders in the sites directory such as 127.0.0.1 or localhost:

> ip/ipconfig loopback add 127.0.0.1

## Useful links

- [Rc - The Plan 9 Shell](http://doc.cat-v.org/plan_9/4th_edition/papers/rc)
- [Setup CPU Server on RPI](https://luksamuk.codes/posts/plan9-setup-rpi.html#org495babf)
- [9front FQA](http://fqa.9front.org/fqa8.html#8.6.1)
- [Contrib package manager](https://plan9docs.wordpress.com/2012/05/08/getting-getting-contributed-packages-installed-on-plan9)