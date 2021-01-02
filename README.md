# Philips_Saphi_SinricPro
ESP8266 sketch that allows you to control Philips Saphi smart tvs with JointSpace API over the internet and with Amazon Echo tanks to SinricPro

This sketch was based on SinricPro, but modified for Philips Saphi TV. You can use is freely to turn on/off you tv, set volume, mute and change inputs.

HOW TO USE
 
 -requirements
	
    1. You will need a Sinric.pro account (this is amazing and you get to add 3 devices for free)
    2. ESP8266 board (I use a WeMos D1 mini)
    3. a Philips TV with Saphi OS (this might work with some of Philips's Android TVs, but I haven't tried it)
    4. The IPAddress of the TV
    5. Your TV's MAC address
    6. Amazon echo device or app for voice control or Sinric.pro app for iOS or Android.    
 
 -sketch upload
 
    1. add your Wi-Fi SSID and Password
    2. add your Sinric.pro credentions
    3. change the placeholder IP address (192.168.1.15) with your own
    4. upload the sketch and profit
 
 THINGS THAT WORK
 
      1. For turning the tv off a key input is send with "Standby" command
      2. For turning the TV on a wake on lan package is send and after this a key input for "Standby" this operation take a bit too long resulting in Alexa saying the tv
      is not responding, but shortly after that the tv should turn on.
      3. setting volume is ass simple as saying "Alexa, set tv volume to 40". Because Sinric.pro works with percents and Saphi goes to 60, no failsafe was implemented
      4. Switching inputs work only for HDMI 1 and HDMI 3 for now. because Saphi OS does not allow for direct input switching I implemented a workaround where an input
      key is send for "Source" then the left arrow is pressed 9 times to go to the left most option and the right arrow is pressed to go to the selected source followed   by confirmation key to activate the source.
      5. Mute/Unmute function is working as intented.
 
 THINGS THAT DON'T WORK
 
      1. switching inputs to anything but HDMI 1(Playstation 4) and HDMI 3(TV) do not work right now.
      3. hardware interaction with remote does not update the sinric.pro device status. Changing volume from remove, on/off, changing sources from remote, mute/unmute.
      These will be fixed in the future.
      
      Tested on philips 43PUS6703/12
      
      I did this for my personal use, but if you find it useful and want to buy me a beer you can do so on https://www.paypal.me/yordantrufchev
