# Iridium (IRD) cryptocurrency core

[![GitHub Release Date](https://img.shields.io/github/release-date/iridiumdev/Iridium-IRD-Core?color=lightgrey&label=Latest%20release&logo=github&style=plastic)](https://github.com/iridiumdev/Iridium-IRD-Core/releases/latest)
[![GitHub last commit](https://img.shields.io/github/last-commit/iridiumdev/Iridium-IRD-Core?color=lightgrey&logo=github&style=plastic)](https://github.com/iridiumdev/Iridium-IRD-Core/commits)
[![GitHub commits since tagged version](https://img.shields.io/github/commits-since/iridiumdev/Iridium-IRD-Core/v5.0.0?color=lightgrey&label=commits%20since%20latest%20release&logo=github&style=plastic)](https://github.com/iridiumdev/Iridium-IRD-Core/commits)

<img src="https://www.ird.cash/wp-content/uploads/2019/01/iridium.svg" width="200" height="200">

Iridium is a cryptonight based cryptocurrency (ticker : IRD)

This is the iridium core source code and binary release.

[Main website](http://www.ird.cash)

[BitcoinTalk main Iridium (IRD) announcement thread](https://bitcointalk.org/index.php?topic=2150442.0;all)

[Iridium (IRD) Desktop Wallet (source and binaries)](https://github.com/iridiumdev/Iridium-IRD-wallet)

[Iridium (IRD) Graphicals Assets](https://github.com/iridiumdev/Iridium-IRD-Graphical-Assets)

[![Twitter Follow](https://img.shields.io/twitter/follow/iridiumcash?label=Twitter&color=lightgrey&logo=Twitter&style=plastic)](https://www.ird.cash)
[![Discord](https://img.shields.io/discord/363789167274098688?label=Discord&color=lightgrey&logo=Discord&style=plastic)](https://discord.gg/xU85tpS)
[![Subreddit subscribers](https://img.shields.io/reddit/subreddit-subscribers/IridiumCoin?color=lightgrey&label=Reddit&logo=Reddit&logoColor=orange&style=plastic)](https://www.reddit.com/r/IridiumCoin)

Libraries needed : boost >=1.58

**development branch is now the default behavior, with blood and tears.**

If you want to compile the latest stable release, currently in production, clone the master branch :
```
git clone -b master https://github.com/iridiumdev/iridium.git
```

Compilation informations : 
```
$ git clone -b master https://github.com/iridiumdev/iridium.git
$ cd iridium
$ mkdir iridium-build
$ cd iridium-build
$ cmake -D STATIC=ON -D CMAKE_BUILD_TYPE=RELEASE ..
$ PORTABLE=1 make
```
