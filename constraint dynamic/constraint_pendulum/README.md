# Background
This simulation use **Impulse-Based Dynamics** with processing 3.3.7 demo
Impulse-Based Dynamics is different from Newton, that is, force method or parametric way to draw the trajectory, it will define a constraint function(hyperplane) to confine the orignial function.

In this pendulum case
original function:
(x,y) = (x_0,y_0 + 0.5 * g * t^2)
constraint function:
C(q) = 0.5 * (q dot q - l^2)
C : R^2 -> R 
q is a vector , q=(x,y)
![](https://i.imgur.com/pF6XaPm.gif)
