# Sparrow
Sparrow is a lightweight game engine framework implemented with Entity-component-system architecture in C++. It made heavy 
use of template meta-programming to enforce type-safe component management.

This project is inspired by the the presentation of Timothy Ford from GDC conference. The overwatch team's success demonstrated
the feasibility of entity-component-system architecuture in the industry.
Traditional game architecture(at least the ones I have worked on) made heavy use of OOP design. However, the data encapsulation 
aspect of OOP is really not helping game development. A video game is a huge complicated product that different systems need 
to constantly communicating with each other. To keep the data encapsulation property of OOP, redundant manager classes or 
convoluted data injection are created. This will only worsen the problem. 

Entity-Component-System architecture is addressing this problem nicely by combining functional programming and object oriented programming together.
