
% knowledge base
flight(edirne, edremit).
flight(edremit, erzincan).

flight(istanbul, izmir).
flight(izmir, isparta).
flight(isparta, burdur).

flight(istanbul, antalya). % the fact that Istanbul and Antalya has a flight.
flight(antalya, gaziantep).
flight(gaziantep, istanbul).
flight(antalya, konya).
flight(konya, ankara).
flight(ankara, istanbul).
flight(ankara, van).
flight(van, istanbul).
flight(van, rize).
flight(rize, istanbul).

% rules
flights(X, Y) :-
	flight(X, Y) ; flight(Y, X).

route(X,Y) :-
	findall(Z, flights(X, Z), Bag),
	(member(Y, Bag);
	route(X, Y, [X], Bag)).

route(_, _, _, []) :- false.
route(X, Y, VisitedList, [Element|List]) :-
	flight(Element, Y);
	not(is_sublist([Element|List], VisitedList)),
	findall(Z, flights(Element, Z), Bag),
	(not(member(Element, VisitedList)), route(X, Y, [Element|VisitedList], Bag);
	route(X, Y, [Element|VisitedList], List)).

print_list([]).
print_list([X|List]) :-
	write(X), nl,
	print_list(List).

is_sublist([],_).
is_sublist([X|List], SecondList) :-
	member(X, SecondList),
	is_sublist(List, SecondList).

