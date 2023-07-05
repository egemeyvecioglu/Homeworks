:- module(main, [is_vote_wasted/2, is_candidate_elected/2, candidate_count_from_city/3, all_parties/1, all_candidates_from_party/2, all_elected_from_party/2, election_rate/2, council_percentage/2, alternative_debate_setups/2]).
:- [kb].

% DO NOT CHANGE THE UPPER CONTENT, WRITE YOUR CODE AFTER THIS LINE

is_vote_wasted(City, PoliticalParty):-
    not(elected(City, PoliticalParty, _)).
    
is_candidate_elected(Name, PoliticalParty):-
    elected(City, PoliticalParty, ElectedRepresentativeCount),
    candidate(Name, PoliticalParty, City, Row),
    Row =< ElectedRepresentativeCount.

candidate_count_from_city(ListOfCandidates, GivenCity, Count):-
    candidate_count_from_city_helper(ListOfCandidates, GivenCity, 0, Count).

candidate_count_from_city_helper([], _, Count, Count).
candidate_count_from_city_helper([Candidate|Rest], GivenCity, Acc, Count):-
    (candidate(Candidate, _, City, _) -> (City = GivenCity -> Acc2 is Acc + 1 ; Acc2 is Acc)),
    candidate_count_from_city_helper(Rest, GivenCity, Acc2, Count).

all_parties(ListOfPoliticalParties):-
    findall(PoliticalParty, party(PoliticalParty, _), ListOfPoliticalParties).
    
all_candidates_from_party(PoliticalParty, ListOfCandidates):-
    findall(Candidate, candidate(Candidate, PoliticalParty, _, _), ListOfCandidates).
    
all_elected_from_party(PoliticalParty, ListOfElected):-
    findall(Candidate, is_candidate_elected(Candidate, PoliticalParty), ListOfElected).

all_elected(ListOfElected):-
    findall(Candidate, is_candidate_elected(Candidate, _), ListOfElected).

election_rate(PoliticalParty , Percentage ):-
    all_candidates_from_party(PoliticalParty, ListOfCandidates),
    all_elected_from_party(PoliticalParty, ListOfElected),
    length(ListOfCandidates, CandidateCount),
    length(ListOfElected, ElectedCount),
    Percentage is  (ElectedCount / CandidateCount),
    format('~2f', Percentage).

council_percentage(PoliticalParty, Percentage):-
    all_elected(ListOfElected),
    all_elected_from_party(PoliticalParty, ListOfElectedFromParty),
    length(ListOfElected, ElectedCount),
    length(ListOfElectedFromParty, ElectedFromPartyCount),
    Percentage is (ElectedFromPartyCount / ElectedCount),
    format('~2f', Percentage).

insert(El,RemList,[El|RemList]).
insert(El,[A|RemList],[A|R]) :- insert(El,RemList,R).

permut(_,[],0).	
permut(List,[El|RestPerm],N) :- N>0,M is N-1,
		insert(El,Rest,List),permut(Rest,RestPerm,M).

alternative_debate_setups(DescriptionString, OrderedListOfCandidates) :-
    string_chars(DescriptionString, PartyInitials),
    length(PartyInitials, NumOfParties),
    findall((Candidate, PoliticalParty), candidate(Candidate, PoliticalParty, _, _), AllCandidates),
    permut(AllCandidates, PermutationsOfAllCandidates, NumOfParties),
    valid_setup(PartyInitials,PermutationsOfAllCandidates ,OrderedListOfCandidates).

valid_setup(_, [], []).
valid_setup([Initial|Initials], [(Candidate, Party)|Rest], OrderedListOfCandidates) :-
    party(Party, Initial),
    valid_setup(Initials, Rest, OrderedListOfCandidates2),
    OrderedListOfCandidates = [Candidate|OrderedListOfCandidates2].
