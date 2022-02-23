% 4.1. Define a Prolog predicate “element(E,S)” that returns true if E is in S.
element(_, []) :- false.
element(E,[S|List]) :-
	E = S;
	element(E, List).

% 4.2. Define a Prolog predicate “union(S1,S2,S3)” that returns true if S3 is the union of S1 and S2.
union_merge([], L, L).
union_merge([S|Set1], S2, [S|Set3]) :-
	union_merge(Set1, S2, Set3).

union_helper([],_):-true.
union_helper([X|List], Y):-
	element(X, Y),
	union_helper(List, Y).

union(S1, S2, S3) :-
	union_merge(S1, S2, S4),
	union_helper(S3, S4),
	union_helper(S4, S3).

% 4.3. Define a Prolog predicate “intersect(S1,S2,S3)” that returns true if S3 is the intersection of of S1 and S2.
intersect(S1, S2, S3) :-
	write("Not implemented yet, TODO: HERE").
	
% 4.3. Define a Prolog predicate “equivalent(S1,S2)” that returns true if S1 and S2 are equivalent sets.
equivalent(S1, S2) :-
	union_helper(S1, S2),
	union_helper(S2, S1).

