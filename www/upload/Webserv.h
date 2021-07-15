


#
i
f
n
d
e
f
 
W
E
B
S
E
R
V
_
H


#
 
d
e
f
i
n
e
 
W
E
B
S
E
R
V
_
H




#
i
n
c
l
u
d
e
 
<
s
y
s
/
s
o
c
k
e
t
.
h
>


#
i
n
c
l
u
d
e
 
<
u
n
i
s
t
d
.
h
>


#
i
n
c
l
u
d
e
 
<
n
e
t
i
n
e
t
/
i
n
.
h
>


#
i
n
c
l
u
d
e
 
<
s
t
r
i
n
g
.
h
>


#
i
n
c
l
u
d
e
 
<
s
y
s
/
t
y
p
e
s
.
h
>


#
i
n
c
l
u
d
e
 
<
s
y
s
/
s
t
a
t
.
h
>


#
i
n
c
l
u
d
e
 
<
f
c
n
t
l
.
h
>


#
i
n
c
l
u
d
e
 
<
i
o
s
t
r
e
a
m
>


#
i
n
c
l
u
d
e
 
<
s
s
t
r
e
a
m
>
 


#
i
n
c
l
u
d
e
 
<
f
s
t
r
e
a
m
>


/
/
#
i
n
c
l
u
d
e
 
"
p
a
r
s
i
n
g
/
p
a
r
s
i
n
g
.
h
p
p
"


#
i
n
c
l
u
d
e
 
<
u
t
i
l
i
t
y
>
 


#
i
n
c
l
u
d
e
 
<
s
t
d
i
o
.
h
>


#
i
n
c
l
u
d
e
 
<
s
t
d
l
i
b
.
h
>


#
i
n
c
l
u
d
e
 
<
d
i
r
e
n
t
.
h
>


#
i
n
c
l
u
d
e
 
"
v
e
c
t
o
r
"


#
i
n
c
l
u
d
e
 
<
s
y
s
/
s
t
a
t
.
h
>


#
i
n
c
l
u
d
e
 
<
s
y
s
/
p
o
l
l
.
h
>


#
i
n
c
l
u
d
e
 
<
s
y
s
/
w
a
i
t
.
h
>


#
i
n
c
l
u
d
e
 
<
e
r
r
n
o
.
h
>


#
i
n
c
l
u
d
e
 
<
n
e
t
i
n
e
t
/
i
n
.
h
>


#
d
e
f
i
n
e
 
T
R
U
E
 
 
 
 
 
 
 
 
 
 
 
 
 
1


#
d
e
f
i
n
e
 
F
A
L
S
E
 
 
 
 
 
 
 
 
 
 
 
 
0




t
y
p
e
d
e
f
 
s
t
r
u
c
t
 
s
_
r
e
s
p
o
n
s
e


{


	
i
n
t
 
c
o
d
e
;


	
s
t
d
:
:
s
t
r
i
n
g
 
p
a
t
h
;


	
b
o
o
l
 
a
u
t
o
i
n
d
e
x
;


	
b
o
o
l
 
c
a
n
_
u
p
l
o
a
d
;


	
s
t
d
:
:
v
e
c
t
o
r
 
<
s
t
d
:
:
p
a
i
r
<
i
n
t
,
 
s
t
d
:
:
s
t
r
i
n
g
>
 
>
 
e
r
r
P
a
g
e
s
;


	
u
n
s
i
g
n
e
d
 
i
n
t
 
m
a
x
B
o
d
y
S
i
z
e
;


	
s
t
d
:
:
s
t
r
i
n
g
 
b
o
d
y
;


	
s
t
d
:
:
s
t
r
i
n
g
 
m
e
t
h
o
d
;


	
s
t
d
:
:
s
t
r
i
n
g
 
d
e
f
a
u
l
t
D
i
r
;


	
s
t
d
:
:
s
t
r
i
n
g
 
n
a
m
e
;


	
s
t
d
:
:
s
t
r
i
n
g
 
l
o
c
a
t
i
o
n
;


	
s
t
d
:
:
s
t
r
i
n
g
 
o
l
d
p
a
t
h
;


	
s
t
d
:
:
s
t
r
i
n
g
 
u
p
l
o
a
d
P
a
t
h
;


}
	
	
	
	
t
_
r
e
s
p
o
n
s
e
;




t
y
p
e
d
e
f
 
s
t
r
u
c
t
 
s
_
r
e
q
u
e
s
t


{


	
s
t
d
:
:
s
t
r
i
n
g
 
m
e
t
h
o
d
;


	
s
t
d
:
:
s
t
r
i
n
g
 
p
a
t
h
;


	
s
t
d
:
:
s
t
r
i
n
g
 
h
t
t
p
;


	
s
t
d
:
:
s
t
r
i
n
g
 
b
o
d
y
;


	
s
t
d
:
:
s
t
r
i
n
g
 
h
o
s
t
;


	
i
n
t
 
p
o
r
t
;


	
s
t
d
:
:
s
t
r
i
n
g
 
t
y
p
e
;


	
i
n
t
 
s
i
z
e
;


	
b
o
o
l
 
i
s
U
p
l
o
a
d
;


	
s
t
d
:
:
s
t
r
i
n
g
 
u
p
l
o
a
d
N
a
m
e
;


	
i
n
t
 
c
o
d
e
;


}
	
	
	
	
t
_
r
e
q
u
e
s
t
;




t
y
p
e
d
e
f
 
s
t
r
u
c
t
 
s
_
s
o
c
k
e
t


{


	
i
n
t
 
p
o
r
t
;


	
i
n
t
 
s
o
c
k
e
t
;


	
s
t
r
u
c
t
 
s
o
c
k
a
d
d
r
_
i
n
 
a
d
d
r
e
s
s
;


	
i
n
t
 
a
d
d
r
l
e
n
;




}
t
_
s
o
c
k
e
t
;




v
o
i
d
 
p
r
i
n
t
R
e
s
p
o
n
s
e
(
t
_
r
e
s
p
o
n
s
e
 
t
)
;


i
n
t
 
i
s
W
o
r
d
(
i
n
t
 
i
,
 
i
n
t
 
i
n
c
r
,
 
s
t
d
:
:
s
t
r
i
n
g
 
s
t
r
)
;


i
n
t
 
i
n
t
l
e
n
(
i
n
t
 
i
)
;


s
t
d
:
:
s
t
r
i
n
g
 
i
n
t
T
o
S
t
r
i
n
g
(
i
n
t
 
i
)
;


v
o
i
d
 
i
n
i
t
R
e
s
p
o
n
s
e
(
t
_
r
e
s
p
o
n
s
e
 
&
t
)
;


v
o
i
d
 
i
n
i
t
R
e
q
u
e
s
t
(
t
_
r
e
q
u
e
s
t
 
&
t
)
;


v
o
i
d
 
p
r
i
n
t
A
l
l
R
e
q
u
e
s
t
(
t
_
r
e
q
u
e
s
t
 
t
)
;


b
o
o
l
 
I
s
P
a
t
h
E
x
i
s
t
(
c
o
n
s
t
 
s
t
d
:
:
s
t
r
i
n
g
 
&
s
)
;


c
h
a
r
 
*
n
e
w
S
t
r
(
s
t
d
:
:
s
t
r
i
n
g
 
s
o
u
r
c
e
)
;


#
e
n
d
i
f



-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
3
7
6
0
4
5
6
9
1
1
2
0
4
9
2
7
1
7
0
2
2
6
8
6
5
9
6
4
2



C
o
n
t
e
n
t
-
D
i
s
p
o
s
i
t
i
o
n
:
 
f
o
r
m
-
d
a
t
a
;
 
n
a
m
e
=
"
s
u
b
m
i
t
"






U
p
l
o
a
d



-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
-
3
7
6
0
4
5
6
9
1
1
2
0
4
9
2
7
1
7
0
2
2
6
8
6
5
9
6
4
2
-
-



