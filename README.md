# brasmecanique
7robot's Mechanical arm project

Idea
----
Ok, we have 5-axis mechanical arm with pipe and pump. What can we do with it? Distribute beer!

There is working PIC-based PCB for controlling arm's motors and reading POTs. So what I propose:

1. for the PIC - write a software for smooth arm movement to desired coordinates. PIC will receive coordinates from Raspberry via UART (see next)

2. use RaspberryPI,  OpenCV and camera somewhere above the table looking downwards to detect empty cups. 

So I see an algorithm like:

- user puts empty cup anywhere he wants on the table
- Rasperry detects coordinates of a cup and sends it to PIC
- PIC moves arm nicely and smoothly to this coordinates, pours out full cup and returns to waiting state

Optional features nice to make:
- move nozzle from bottom of the cup to top while pouring to minimize foam
- somehow detect cup top to always distribute full cup independant of it's volume (in this case we will not even need liquid flow sensor)

Repo structure
----
<b>Hardware</b> everything about hardware, mailly PIC board schematic

<b>PIC</b> PIC's software - arm movement

<b>Raspberry</b> Raspberry's software - cup detection


Monetization
----
1. add cash acceptor
2. bring this thing to crowdy place or sell to a bar
3. ???
4. PROFIT!
