# displayPM

A display for sensor.community.

This is my first project on github, so sorry if not all rules here are respected.
I'm not new to programming, in fact I wrote my first program in assembler 8085 back in 1977.

In 2019 the need arised to show measured PM values from the Luftdaten network, now sensor.community, 
to the general public, on a big stand-alone display, consisting of 16 LED blocks 8*8 dotmatrix, driven by Max.7219,
and an ESP8266 controller to make the connection between the display and the dataserver on the internet.

Although it was the intention to distribute the sourcecode on github from the beginning, COVID intervened,
and prevented the rollout of the display in Belgium.
So the whole project was put on hold in the first half of 2020, including making the source program public.

At that time the virtual connection to one or two meters was implemented & working.

The one meter configuration had its measurements explained.

The two meter configuration could be a PM meter outside, and one inside the same home, with the measuments compared & explained.
Also a configuration with two outside meters was supported, also with measurements compared & explained.

In 2023, things started to move again, and after a small overhaul & debugging session starting in June, new features were implemented.
A start was made to show 24 hour peak values, with local storage for calculating it. This is not yet operational.

A start was made for monitoring more than the two meters already supported.
The display can now be used as a monitoring device for an unlimited number of sensors, while limiting the messages 
to show only the mean value, and the exceptions with their identification.

More new features will follow:

- Showing results from the DNMS system (digital noise measuring system) from sensor.community.
- 
- Showing the results of Telraam, another project here in Belgium, to count traffic according category.
- 
- A web interface for configuring, as the configuration now is through editing the sourcecode & recompiling,
  limiting the rollout by non-programmers.

Building & explaining sessions will be held starting starting March 2, 2024 in HackerSpace Brussels, Osseghemstraat 53, 1060 Molenbeek-Belgium.
If you want to participate, please enroll via https://www.meetup.com/nl-NL/civic-lab-brussels/

Extensions & corrections to the sourcecode will be made public through this channel.
   

