
:- dynamic(student	/3).
:- dynamic(course	/6).
:- dynamic(room		/3).
:- dynamic(occup	/3).

%%% Knowledge Base %%%

% Room: id, capacity, special_equipment
room(z24, 100, [nothing]).

% Occupancy information: room_id, hour, name_of_the_course_taking_that_hour
occup(z24, 1, cse341).
occup(z24, 3, cse443).
occup(z24, 5, cse454).
occup(z24, 9, cse476).

% Course: id, instructor, capacity, one_or_more_hours, room_information, special_needs
course(cse341, yakup_genc, 100, 3, z24, nothing).
course(cse443, erchan_aptoula, 100, 3, z24, nothing).
course(cse454, burcu_yilmaz, 100, 3, z24, nothing).
course(cse476, hasari_celebi, 100, 2, z24, nothing).

% Instructor: id, several_courses, preferences
% ---

% Student: id, list_of_courses, A_student_can_also_be_handicapped(t/f)
student(111, [cse101, cse107], nothing).


%%% Rules %%%

% Your expert system should be able to add a new student, course or a room to the system.

% add student
add_student(Id, A, B):-
	\+ student(Id, _, _),
	assert(student(Id, A, B)).

% add course
add_course(Id, A, B, C, D, E) :-
	\+ course(Id, _, _, _, _, _),
	assert(course(Id, A, B, C, D, E)).

% add room
add_room(Id, A, B) :-
	\+ room(Id, _, _),
	assert(room(Id, A, B)).

% It should respond to queries such as:

% Check whether there is any scheduling conflict.
scheduling_conflict(Course1, Course2) :-
	course(Course1, _, _, T1, Room1, _),
	course(Course2, _, _, T2, Room2, _),
	Room1 == Room2,
	occup(Room1, H1, Course1),
	occup(Room2, H2, Course2),
	End1 is T1 + H1,
	End2 is T2 + H2,
	(((H1 =< H2), (H2 < End1)), ! ; ((H2 =< H1), (H1 < End2))).

% Check which room can be assigned to a given class.
% Check which room can be assigned to which classes.
room_assign_class(Room, Course) :-
	room(Room, Cap_r, Seq),
	course(Course, _, Cap_c, _, Room, Sneed),	
	Cap_c =< Cap_r,
	member(Sneed, Seq).

% Check whether a student can be enrolled to a given class.
% Check which classes a student can be assigned.
enrolled_to_class(Student, Course) :-
	student(Student, Loc, Needs_s),
	course(Course, _, _, _, Room, _),
	room(Room, _, Needs_r),
	\+ member(Course, Loc),
	member(Needs_s, Needs_r).
