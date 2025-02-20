+++
title = "Technological Privacy Crises"
date = 2023-06-02
description = "Let me just make a TikTok quickly, OMG look at the food here - I gotta post it on Instagram..."

[taxonomies]
tags = ["digital privacy", "cybersecurity", "open source", "data sovereignty", "encryption", "surveillance", "tech alternatives", "Linux", "mobile security", "VPN", "secure messaging", "password management", "cloud storage", "social media", "browser privacy"]
categories = ["Technology & Privacy"]

[extra]
image = "/images/writings/technology_crisis.jpg"
image_alt = "Technological Privacy Crises"
read_time = "15 min read"
+++

# Going Down the Rabbit Hole...
When you start digging deeper into how each layer of our everyday technology functions, it might shock you that there are multiple opportunities for the government and big companies to integrate a backdoor that give them unrestricted access to your data, or simple trackers that monitor your everyday move.

I used to reject most apps and platforms if I could not see the source code. The reason being that whenever we use proprietary software, which could even be as simple as a driver for a LED keyboard we give up the ability to see what is going on inside our device and we most likely give up some of our privacy.

Most proprietary software comes with trackers that will log certain information and metadata about you.

When applications make a claim that they use "end-to-end encryption" but the frontend source code is not available there is no way for experts to check if they are actually using military grade encryption and they they have not implemented a backdoor to access your information.

Frontend source code is the software running on your device, and it is the part that would be responsible for any end-to-end encryption. The other part of the software is the backend software, which is run on a server.

## Governments love your data...
Edward Snowden is known for releasing a lot of confidential information about how the NSA operates and has made the public aware of [PRISM](https://en.wikipedia.org/wiki/PRISM), a program with the entire purpose of collecting all kinds of data about its citizens.

More recently we also have the [Twitter files](https://jordansather.substack.com/p/running-list-of-all-twitter-files) revealing how close the government actually works with big tech giants. The first step for more privacy is to get informed, about what is actually happening in the tech world and what alternatives are out there.

Data is money and power. The more you can hoard, the more powerful you can become.

We only need to look at China to see what a society could become when we let the governments have unrestricted access to our data. With social credit systems and no privacy for their citizens the list of terrifying things happening in that continent are endless.

We have people getting [arrested](https://twitter.com/clipsthatgohard/status/1662473734949851136?s=20) who simply complain about some bad behavior from a police officer in a "private" group chat.

You are not allowed to disobey. You must cohere with those above you. You are just an animal in a open prison system in that society.

We know we wouldn't like to live in a society with such restrictions on freedom. Yet the west seems to be heading down the same path as China!

With new surveillance programs and laws limiting freedom of speech, punishing those who speak up against the narrative.

If the data is not in our secure hands and you are not inline with whatever the most powerful individuals want you to believe and say, then that data will be used against you!

## Not even your hardware is safe
There are many layers to this problem, including the core part of what makes computing even possible.

For example all modern Intel CPU chips are running another operating system called [Minix](https://itsfoss.com/fact-intel-minix-case/) which can auto update and has access to your RAM and CPU, while at the same time remaining completely inaccessible to the user.

Even [motherboards](https://www.wired.com/story/gigabyte-motherboard-firmware-backdoor/) can come with a build-in backdoor, it is hard to know what hardware we can trust if the schematics are not open to the public. And thus this issue to become more private and secure because a lot deeper than simply switching the software we use in our everyday life.

In this article however I will be focusing on the software part and not hardware. Even if there are many layers to this problem, simply removing some of the data vulnerability is already a grand step to reaching more privacy.

Below I have devised a comprehensive list of software tools of everyday applications that I find extremely useful to protect my data.

![Cyborg Love](/images/writings/cyborg_love.jpg)

# Improving your data sovereignty.
Finding alternatives to our everyday tools can be time consuming and can require deeper technological knowledge to evaluate what a good alternative needs to have. I have invested hundreds of hours to find the best applications that will give you more data privacy and sovereignty.

## Desktop OS
Windows comes with preinstalled trackers and spyware, sending data about your usage daily to windows servers. It is possible to remove all of those windows applications such as by installing [AtlasOS](https://atlasos.net/) which would in theory give you more privacy.

However you will also loose all the security updates and features, making the system easier to hack and if not used careful it could become infested by viruses and other spyware.

MacOS might appear as a more secure and private alternative. However MacOS has similar issues as Windows regarding privacy. The firmware and the software is proprietary and might very well have a backdoor installed for the government.

You will forced to rely on MacOS updates to stay secure from hackers, yet at any point it time it could also be used to install spyware from Apple that could compromise your privacy.

This can happen for various reasons and since the Apple updates are not transparent and a lot of the software is proprietary it is a real possibility that this might happen.

Thus if you truly want to switch to a more private and secure desktop system you will need to invest time and energy in learning to use a Linux distributions.

### Linux

You can install a second operating system on your laptop or desktop and dual boot with Linux, allowing you to switch back and forth and familiarize yourself with the new environment. Most servers that keep the internet alive today run Linux, making it one of the most secure and privacy-respecting systems to use.

There are many different flavors of Linux distributions (distros). Here are a few recommendations:

- For beginners and general users: [Pop!_OS](https://pop.system76.com/)
- For security: [QubesOS](https://www.qubes-os.org/)

Pop!_OS is highly recommended for several reasons:
1. User-friendly and modern COSMIC desktop environment
2. Great app access through Flatpak and Ubuntu packages
3. Productivity features like tiling window manager

QubesOS is ideal if security and privacy are your primary concerns, running applications in separate containers. However if you are not familiar with linux systems you will be easily overwhelmed!


## Mobile OS
On Mobile the world looks a little bit different. In general Mobile systems are more secure than a Desktop OS, with applications needing to request permission to access your sensors and data your privacy is safer.

There are still some vital flaws that need to be taken into consideration.

First of all, I will just say it clear as day. If you are running iOS try to switch to Android.

Russia [claims](https://www.reuters.com/world/europe/kremlin-tells-officials-stop-using-iphones-kommersant-newspaper-2023-03-20/) that iPhone's have a backdoor that sends information the CIA, thus any applications no matter how secure will still leak data to certain governmental organization.

Apple devices might be quite secure from third party trackers and other spyware, but you are not safe from Apple itself, they have full control over your device and could do whatever they want. You do not truly own your device.

### Android
Android devices can also come with a backdoor made by the manufacturer, and it is hard to know what you can truly trust. We can try to increase our privacy by installing a custom ROM on our device such as [LineageOS](https://lineageos.org/) and [GrapheneOS](https://grapheneos.org/).

Android by default comes preloaded with many proprietary application which cannot be uninstalled unless you flash a custom ROM.

Google has managed to create an ecosystem around google play services. Getting rid of it will make some applications not work anymore.

This is how Google tries to stay in control of their otherwise free and open source operating system. It can be a tedious job to try to make your Android device truly private.

If privacy and security is your NO. 1 concern, I would recommend you to get a Google Pixel device and install [GrapheneOS](https://grapheneos.org/).

If you want to learn more about GrapheneOS you can watching [this](https://www.youtube.com/watch?v=xIXAzA555xk) video by The Hated One.

On most other devices you can try to unlock the bootloader and install LineageOS.

This will give you more freedom over your device and let you choose if you want to have Google apps or not.

There are a few manufacturers that let you easily install a custom ROM.

If you are looking to buy a new device that can probably be trusted to not have a malicious backdoor I would recommend taking a look at the [Fairphone](https://shop.fairphone.com/) and the [Shiftphone](https://www.shiftphones.com/en/).

### Privacy Respecting Apps for Android

Reaching more privacy is not easy, but there are many great tools on Android that you can use to make your life a little bit more private. Below are a few of my favorite privacy respecting applications for Android.

 - [F-droid](https://f-droid.org/en/)
 - [NewPipe](https://newpipe.net/)
 - [Simple Mobile Tools](https://www.simplemobiletools.com/)
 - [AdAway](https://adaway.org/)

F-droid is an alternative app store with only open source tools, no spyware, no tracking, just applications you can trust

NewPipe is an alternative front-end to YouTube allowing you to listen to music in the background or download any video while not having to watch any adverts.

Simple Mobile Tools is a collection of standard applications that are fully open source and do not have any trackers.

AdAway allows you to block advertisements on your device, either by using a local VPN to redirect traffic or by changing the hosts file if you have [root](https://en.wikipedia.org/wiki/Rooting_(Android)) access.

## Web Browser
The web browser is arguably the most important piece of software on your device, giving you access to a near infinite pool of information.

With most people using Chrome we lean into the convenience of Google taking care of all our passwords, browser history and searches we make.

However there are great alternatives that will give you the modern browsing experience while respecting your privacy. My number one choice is [Brave](https://brave.com/).

I have used it for years. I love that it blocks the cookie consent forms and that it has an inbuilt ad-block. It is based on chromium which is the open source layer powering Chrome, with added functionality and protection.

At [PrivacyTests.org](https://privacytests.org/) we can view what browser has the best privacy protection. [LibreWolf](https://librewolf.net/) and the [Mullvad Browser](https://mullvad.net/en) are two other great options if you prefer a Firefox based browser.

No matter what browser you choose, I highly recommend getting [uBlock Origin](https://ublockorigin.com/), as it is the best extension to block trackers and remove advertisements.

## VPN or Tor
I get a lot of people asking me about VPNs. I gotta tell you, most of these sponsored VPNs on YouTube are most likely untrustworthy and probably still log some of your data.

In fact most popular VPNs are owned by a [few](https://vpnpro.com/blog/hidden-vpn-owners-unveiled-97-vpns-23-companies/) companies.

For example ExpressVPN, CyberGhost VPN and Private Internet Access (PIA) are all owned by Kape Technology. Before they changed their name, the company would inject code into the users devices to track information...

They also own a lot of the review sites for VPNs so of course they give a great rating to all their products...

The whole idea of VPNs is to hide traffic from the Internet Service Provider, and to not have your internet tracked.

I am not an expert in what VPN you should use or which one can be trusted. I think [Mullvad VPN](https://mullvad.net/en) might be a good option.

In either case, if you must hide your internet traffic, you will need to download the [Tor Browser](https://www.torproject.org/) to access the tor network. It is probably the safest method to hide your IP address if that is what you need to do, however it will come at the cost of performance.

## E-mail
Most of us use Gmail, Yahoo or Outlook. None of these give you any privacy. All the data is accessible by the Companies, the NSA and other governmental organizations.

Currently one great alternative to these email providers while also providing great security and encryption seems to be [Protonmail](https://proton.me/). The UI is great and pricing scheme is reasonable to get all the features you need.

If Proton is not to your liking here are a few more interesting alternative e-mail providers:

 - [Tutanota](https://tutanota.com/)
 - [Disroot](https://disroot.org/)
 - [Skiff](https://skiff.com/mail)

## Cloud Storage
A lot of business and individuals use Google Drive and OneDrive. And it is hard to find an alternative that as convenient.

The closest I have come across is [Nextcloud](https://nextcloud.com/). It is fully open source and you can use it by finding an existing [provider](https://nextcloud.com/providers/) or self hosting it entirely on your own server.

With [Nextcloud Office](https://apps.nextcloud.com/apps/richdocuments) you will be able to share documents and edit them directly in the web browser. This can give you full control over your own data

## Photos
Do you enjoy the convenience of backing up all your photos to the iCloud or Google Photos and being able to access them anywhere? Great, I love it too. And that is why I use ente Photos.

[ente Photos](https://ente.io/) is available on all devices, it is fully open source and uses end-to-end encryption, meaning any photo is encrypted before it is send to their server.

Their pricing scheme is also reasonable. I honestly could not think of a better product to store all my photos and videos!

## Messaging
I gotta admit, WhatsApp and Messenger have one of the best video chat capabilities out there - especially on a bad data connection. However there is a close competitor to both of these Meta messaging apps and that would be [Telegram](https://telegram.org/).

Some people do have privacy concerns about Telegram, but you can make secret chats with end-to-end encryption and verify the source code as the client side software is open source.

The server side code is sadly not open source thus it could be that at some point all the chats that are not in a secret chat go in the hands of the wrong people.

There are many other messaging apps which are more private, but they are harder to use and are not as popular, such as:

 - [Session](https://getsession.org/)
 - [Element](https://element.io/)
 - [SimpleX](https://simplex.chat/)
 - [XMPP](https://xmpp.org/)
 
For a more comprehensive comparison of privacy concerns relating messaging check out
[Secure Messaging Apps](https://www.securemessagingapps.com/).

## Social media
Facebook is a great way to connect with your old long lost buddies, and such a great way to be bombarded by advertising and getting your data sold. And best of all if you speak out against certain narratives your account could be suspended.

[Twitter](https://twitter.com/) has been changing radically since the Elon Musk takeover. He has said many times that he will open source the algorithm and bring freedom of speech back.

[Parts](https://github.com/twitter) of it have been open sourced and a lot of conservative voices have finally been able to return to the platform.

Who knows if it will continue going in a more positive direction, I have my doubts and although it has become a vital place to find out what is going on in the world I would encourage people to learn more about federated social media.

The topic of federated social media is vast and can quickly become very complex for most people - with all the different protocols and platforms.

If you are interested in this topic I recommend checking out some of the notable software powering the [fediverse](https://en.wikipedia.org/wiki/Fediverse).

The fediverse is not governed by a single entity, instead the power is spread out between different instances and nodes in the network.

Anyone can become part of the network and run the software on a server, thus distributing the network further.

 - [Nostr](https://nostr.com/)
 - [Mastodon](https://joinmastodon.org/)
 - [Soapbox](https://soapbox.pub/)

## Password Manager
Some people [wrongfully](https://www.kiplinger.com/personal-finance/lastpass-hack) recommend LastPass as a secure way to generate passwords.

They have been hacked multiple times. Their software is not open source and they potentially have access to all your passwords.  

Having a secure password and enabling Two-Factor Authentication is the best way to keep your account secure.

There are many great open source android applications for Two-Factor Authentication such as [Aegis Authenticator](https://getaegis.app/).

For Linux desktop I recommend using [KDE Keysmith](https://apps.kde.org/keysmith/).

This will allow you to use Two-Factor Authentication without the proprietary Goggle Authenticator or Microsoft Authenticator apps.

To store passwords securely I would recommend trying [Bitwarden](https://bitwarden.com/) (similar to LastPass, but fully open source), [KeePassDx](https://www.keepassdx.com/) (android only) or [LessPass](https://www.lesspass.com/).

LessPass is probably the most interesting one from these recommendations, as you can setup a certain combination, and type in the domain for which you would like to generate a password.

Thus you only need to remember one combination and you can generate a unique password for any website you use. You do not need to store any passwords in any database, as everything is generated directly on your device.

Lastly if finding an alternative way for generating or storing passwords is too much hassle, using the Brave default password manager will give you decent protection and allow you to sync your password between your Brave installations. Giving you the convenience you might be used to.

![Cyber Rabbit](/images/writings/rabbit.jpg)

# Finding your own way
The journey to finding what works for you can be long and the willingness to try something new even longer. What is important is taking small steps and understanding the threat we are facing if governments know our every move and we have no privacy.

The list of alternatives is endless. Luckily you can go to [alternativeto.net](https://alternativeto.net/) and find applications similar to what you are using, and possibly even an open source solution that you can trust.

I once again want to remind that the issue of reaching true privacy is deeper than just changing the software.

Creating an open ecosystem for hardware is a crucial step to reduce the chances of us ending up in a totalitarian world government where all our actions are monitored and controlled by those above us.

There are many noteworthy projects out there that are inspiring to give you more control over your device such as [pine64](https://www.pine64.org/pinephone/), [Raspberry Pi](https://www.raspberrypi.org/), [Fairphone](https://www.fairphone.com/en/) and [System76](https://system76.com/).

To find other great projects you can look at Wikipedia's list of [open hardware projects](https://en.wikipedia.org/wiki/List_of_open-source_hardware_projects) and [open-source mobile phones](https://en.wikipedia.org/wiki/List_of_open-source_mobile_phones).

## Support
If you found this article insightful please consider leaving a tip.

Share this article with your aunt, grandmother, your pets and a stranger down the road to make more people aware about these issues and how they can find more privacy.

Thank you for reading!