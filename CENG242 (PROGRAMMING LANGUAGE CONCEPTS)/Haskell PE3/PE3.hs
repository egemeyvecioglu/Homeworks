{-# LANGUAGE FlexibleInstances #-}

module PE3 where

import Data.List (sort, sortBy)
import Text.Printf (printf)

data Term = Const Integer | Pw Integer Power | Trig Integer Power Trigonometric | Exp Integer Power Exponential

data Power = Power Integer
data Polynomial = Polynomial [(Integer, Power)]
data Exponential = Exponential Polynomial
data Trigonometric = Sin Polynomial | Cos Polynomial

class Evaluable a where
    function :: a -> (Integer -> Double)

class Differentiable a where
    derivative :: a -> [Term]

-- You can use this as is
getRounded :: Double -> Double 
getRounded x = read s :: Double
               where s = printf "%.2f" x

-- You don't have to follow the order the functions appear in the file
-- For example, you could first define all Show instances, then all Eq instances etc.
-- if that implementation order is more convenient for you.



-- INSTANCES FOR POWER

instance Show Power where
    show (Power 0) = "1"
    show (Power 1) = "x"
    show (Power n) = "x^" ++ show n

instance Eq Power where
  (Power p1) == (Power p2) = p1 == p2

instance Ord Power where
  (Power p1) > (Power p2) = p1 > p2
  (Power p1) >= (Power p2) = p1 >= p2
  (Power p1) < (Power p2) = p1 < p2
  (Power p1) <= (Power p2) = p1 <= p2


instance Evaluable Power where
    function (Power p) = \x -> fromInteger x ** fromInteger p

instance Differentiable Power where
    derivative (Power p) = [Pw (fromInteger p) (Power (p-1))]



-- INSTANCES FOR POLYNOMIAL
--data Polynomial = Polynomial [(Integer, Power)]
instance Show Polynomial where
    show (Polynomial []) = "0"
    show (Polynomial [(i, p)]) = (if(i == 1) then "" else if(i == -1) then "-" else show i) ++ (if (p == Power 0) then (if ((abs i) == 1) then "1" else  "") else show p)
    show (Polynomial ((i,p):xs)) = ((if(i == 1) then "" else if(i == -1) then "-" else show i) ++ (if (p == Power 0) then (if ((abs i) == 1) then "1" else  "") else show p)) ++ (foldl (++) "" [myshow (i,p)|(i,p)<-xs])

myshow :: (Integer, Power) -> String
myshow (i,p) = if(i == 0) then "" else ( " + " ++ (if (i == 1) then "" else if(i == -1) then "-" else show i) ++ (if (p == Power 0) then (if ((abs i) == 1) then "1" else  "") else show p))


instance Evaluable Polynomial where
    function (Polynomial lst) = \x -> getRounded $ sum [fromInteger i * ((fromInteger x) ** (fromInteger p))| (i, Power p) <- lst]

instance Differentiable Polynomial where
    derivative (Polynomial []) = []
    derivative (Polynomial ((i,Power p):xs)) = if p == 0 then derivative (Polynomial xs) else (Pw (fromInteger i * fromInteger p) (Power (p-1))) : derivative (Polynomial xs)




-- INSTANCES FOR TRIGONOMETRIC
--data Polynomial = Polynomial [(Integer, Power)]
--data Trigonometric = Sin Polynomial | Cos Polynomial
instance Show Trigonometric where
    show (Cos (Polynomial lst)) = "cos" ++ (if((length lst) > 1 || (length lst == 1 && (snd (head lst) > Power 1) || (fst (head lst) < 0) )) then "(" else "") ++ show (Polynomial lst) ++ (if((length lst) > 1 || (length lst == 1 && (snd (head lst) > Power 1) || (fst (head lst) < 0) )) then ")" else "")
    show (Sin (Polynomial lst)) = "sin" ++ (if((length lst) > 1 || (length lst == 1 && (snd (head lst) > Power 1) || (fst (head lst) < 0) )) then "(" else "") ++ show (Polynomial lst) ++ (if((length lst) > 1 || (length lst == 1 && (snd (head lst) > Power 1) || (fst (head lst) < 0) )) then ")" else "")

instance Evaluable Trigonometric where
    function (Sin poly_list) = \x -> getRounded $ sin (function poly_list x)
    function (Cos poly_list) = \x -> getRounded $ cos (function poly_list x)

instance Differentiable Trigonometric where
    derivative (Cos poly_list) = 
        let lst = derivative poly_list
        in map (\(Pw i p) -> Trig (-i) (p) (Sin poly_list)) lst
    derivative (Sin poly_list) = 
        let lst = derivative poly_list
        in map (\(Pw i p) -> Trig (i) (p) (Cos poly_list)) lst
 




-- INSTANCES FOR EXPONENTIAL
--data Exponential = Exponential Polynomial

instance Show Exponential where
    show (Exponential (Polynomial lst)) = "e^" ++ (if((length lst) > 1 || (length lst == 1 && (snd (head lst) > Power 1) || (fst (head lst) < 0) )) then "(" else "") ++ show (Polynomial lst) ++ (if((length lst) > 1 || (length lst == 1 && (snd (head lst) > Power 1) || (fst (head lst) < 0) )) then ")" else "")

instance Evaluable Exponential where
    function (Exponential poly_list) = \x -> getRounded $ exp (function poly_list x)

instance Differentiable Exponential where
    derivative (Exponential poly_list) = 
        let lst = derivative poly_list
        in map (\(Pw i p) -> Exp (i) (p) (Exponential poly_list)) lst 



-- INSTANCES FOR TERM
--data Term = Const Integer | Pw Integer Power | Trig Integer Power Trigonometric | Exp Integer Power Exponential
--data Polynomial = Polynomial [(Integer, Power)]
--data Trigonometric = Sin Polynomial | Cos Polynomial
--data Exponential = Exponential Polynomial
--e.g : show (       Trig 2 (Power 1) (Cos (Polynomial [(1, Power 1)]))       )
instance Show Term where
    show (Trig i p t) = ((if(i == 1) then "" else( if(i == -1) then "-" else show i)) ++ (if (p == Power 0) then "" else show p)) ++ show t
    show (Exp i p e) =((if(i == 1) then "" else( if(i == -1) then "-" else show i)) ++ (if (p == Power 0) then "" else show p))++ show e
    show (Const i) = show i
    show (Pw i p) =if(i == 1 && p == Power 0) then (show i) else ((if(i == 1) then "" else( if(i == -1) then "-" else show i)) ++ (if (p == Power 0) then "" else show p))

instance Evaluable Term where
    function (Const i) = const (fromInteger i)
    function (Pw i p) = \x -> getRounded $ (fromInteger i) * (function p x)
    function (Trig i p t) = \x -> getRounded $ (fromInteger i) * (function p x) * (function t x)
    function (Exp i p e) = \x -> getRounded $ (fromInteger i) * (function p x) * (function e x)

instance Differentiable Term where
    derivative (Const i) = []
    derivative (Pw i p) = let [(Pw ii pp)] = derivative p in if(i*ii == 0) then [] else [Pw (i*ii) pp]
    derivative (Trig i p t) = case (derivative p, derivative t) of
                                ([], []) -> []
                                ([], [(Trig iii ppp ttt)]) -> if(i*iii==0) then [] else [(Trig (i*iii) p ttt)]
                                ([(Pw ii pp)], []) -> if(ii == 0) then [] else [(Trig (i*ii) pp t)]
                                ([(Pw ii pp)], [(Trig iii ppp ttt)]) -> [(Trig (i*ii) pp t), (Trig (i*iii) p ttt)]
    derivative (Exp i p e) = case (derivative p, derivative e) of
                                ([], []) -> []
                                ([], [(Exp iii ppp eee)]) -> if(i*iii==0) then [] else [(Exp (i*iii) p eee)]
                                ([(Pw ii pp)], []) -> if(ii == 0) then [] else [(Exp (i*ii) pp e)]
                                ([(Pw ii pp)], [(Exp iii ppp eee)]) -> [(Exp (i*ii) pp e), (Exp (i*iii) p eee)]




-- INSTANCES FOR [TERM]

instance Evaluable [Term] where
    function lst = \x -> getRounded $ sum [function term x| term <- lst]

instance Differentiable [Term] where
    derivative lst = 
        let derivatives = [(derivative term) | term <- lst]
        in foldl (++) [] derivatives
    