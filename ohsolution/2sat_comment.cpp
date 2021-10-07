// a^b == (~a || ~b) & (a||b)
// a eq b == (~a||b) &(a||~b)
// a-> b == (~a||b)
// (a+b+c<=1) == (~a||~b) & (~a||~c) &(~b||~c)
// set a =1 (a||a), set a=0 (~a||~a)

/*
A1 ... Ak <=1
mk dummy B1 .. Bk

Bi -> B(i+1)
Ai -> B(i)
Bi -> ~A(i+1)    
*/
    
