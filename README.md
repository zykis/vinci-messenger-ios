# Preparations
sudo gem uninstall cocoapods
sudo gem install cocoapods -v 1.7.5 -n /usr/local/bin/

## Check pod version (should be 1.7.5)
pod --version

## Install carthage
brew update && brew upgrade carthage

# WebRTC
git submodule update --init --recursive

# Pods
pod install

# Carthage dependencies
cd ThirdParty
carthage update --platform iOS
