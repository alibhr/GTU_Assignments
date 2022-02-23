% facts..

% when(X,Y) – time of the course X is Y
when(102, 10).
when(108, 12).
when(341, 14).
when(455, 16).
when(452, 17).

% where(X,Y) – place of the course X is Y
where(102, z23).
where(108, z11).
where(341, z06).
where(455, 207).

% enroll(where(452, 207).X,Y) – student X is enrolled in course Y
enroll(a, 102).
enroll(a, 108).
enroll(b, 102).
enroll(c, 108).
enroll(d, 341).
enroll(e, 455).

% 3.1. Define/write a predicate “schedule(S,P,T)” that associates a student to a place and time of class.
schedule(S, P, T) :-
	enroll(S, Lesson),
	where(Lesson, P),
	when(Lesson, T).

% 3.2. Define/write another predicate “usage(P,T)” that gives the usage times of a classroom.
usage(P, T) :-
	when(P, T).

% 3.3. Define/write another predicate “conflict(X,Y)” that gives true if X and Y conflicts due to classroom or time.
conflict(X,Y) :-
	(where(X, X_class),
	where(Y, Y_class),
	X_class = Y_class,
	X \== Y),
	(when(X, X_time),
	when(Y, Y_time),
	X_time = Y_time,
	X \== Y).
	
% 3.4. Define/write another predicate “meet(X,Y)” that gives true if student X and student Y are present
% in the same classroom at the same time.
meet(X, Y) :-
	schedule(X, PlaceX, TimeX),
	schedule(Y, PlaceY, TimeY),
	PlaceX = PlaceY,
	TimeX = TimeY,
	X \== Y.

