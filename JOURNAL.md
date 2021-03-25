# Journal
This is a journal/logbook of some of my thoughts as I progress through this project.

# Stages 1-2 (Tethered power, moving wheel independently, untethered power)
Since my last Arduino based project I had done two key things: one, taken a course on Udemy called "Microcontroller Embedded C Programming: Absolute Beginners" that used an STM32 Discovery Kit to teach some basics, and: two, started the Harvard CS50x class.

The Udemy course was interesting. It taught some basic concepts but also side by side was teaching things like setting internal registers and doing bitwise math. It taught bitwise shifting before loops, which is not the typical learning order. However, it was some great exposure into what the Arduino platform covers up and how nice it is for prototyping. I felt extremely accomplished when I did the blinking board LED, because it wasn't a simple `delay 50, LED_ON, delay 50, LED_OFF` it was a full on `Set register 0xAB34, bitwise register 0x34CF` etc. We took the board from bare metal to set up and wroking how we wanted to for the LED.

The Harvard CS50x class however, is a masterpiece of teaching. I cannot recommend this (free!) course more to any beginner, or even to someone like me who thought they were a beginner but actually skipped a lot of important foundational learning. I have learned and mastered more about programming in general, and C specifically, in the 3 weeks I've done the course than all of my other experiences combined.

Armed with my new knowledge and practice in coding I was able to put together a working prototype of a car that could move forward, stop, and turn left and right in about 3 hours. (Foreshadowing: it couldn't go left or right after reaching full speed; I had to stop to make turns) These 3 hours were split into 45 minute chunks before work or before the gym, so I did have time inbetween to mull over problems which is extremely helpful. I think ideally I would work in ~90 minute sprints to allow more time to iterate through changes, but also still have time to think about big problems instead of getting stuck on them.

# Stages 3-4 Radio
I'd ordered 4x NRF24L01+ units 2-3 years ago for a project I wanted to do, and was completely overwhelmed by them so I was nervous about getting into them. However, after looking at some sample code I found it was laughably easy to set it up and get a working blinking LED. However, I had issues transitioning it to my own code. After much debugging, it turned out that I had set all my logic and code perfectly fine, but forgot to change the pins. Only half of the radio pins were correct, which meant it would work *sometimes*. 🤦‍♂️

# Stage 5 - State Machine Control
