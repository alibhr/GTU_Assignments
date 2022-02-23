%%% Knowledge Base %%%

flight(canakkale,	erzincan,	6).

flight(erzincan,	antalya,	3).
flight(erzincan,	canakkale,	6).

flight(antalya,		erzincan,	3).
flight(antalya,		izmir,		2).
flight(antalya,		diyarbakir,	4).

flight(izmir,		antalya,	2).
flight(izmir,		ankara,		6).
flight(izmir,		istanbul,	2).

flight(istanbul,	izmir,		2). % fact: Istanbul and Izmir has a flight with cost 2.
flight(istanbul,	ankara,		1).
flight(istanbul,	rize,		4).

flight(ankara,		istanbul,	1).
flight(ankara,		rize,		5).
flight(ankara,		van,		4).
flight(ankara,		diyarbakir,	8).
flight(ankara,		izmir,		6).

flight(rize,		istanbul,	4).
flight(rize,		ankara,		5).

flight(van,			ankara,		4).
flight(van,			gaziantep,	3).

flight(gaziantep,	van,		3).

flight(diyarbakir,	ankara,		8).
flight(diyarbakir,	antalya,	4).

%%% Rules %%%

graph_traversal(X, Y, C, _) :-
	flight(X, Y, C).

graph_traversal(X, Y, C, Visited) :-
	\+ member(X, Visited),
	flight(X, Y1, C1),
	graph_traversal(Y1, Y, C2, [X|Visited]),
	X \= Y,
	C is C1 + C2.

route(X, Y, C) :-		% a predicate indicating there exist a route between
	flight(X, Y, C).	% X and Y if there is flight between X and Y with cost
						% C.

route(X, Y, C) :- 
	graph_traversal(X, Y, C, []).
