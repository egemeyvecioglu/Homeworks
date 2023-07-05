module PE2 where

-- PE2: Dungeon Crawler
-- Dungeon map is :: Tree Chamber [Encounter]
-- Each encounter is either a fight or a treasure
-- Fights deal you damage (reduce HP) but enemies drop some gold (add
-- gold)
-- Tresures just give gold, or potions (which give hp)
-- Nodes hold encounters, when you visit a node you go through all of them in order
-- You start with a certain amount of HP and 0 gold.
-- You lose HP and accumulate gold as you descend the tree and go through encounters

-- Polymorphic tree structure
data Tree a b = EmptyTree | Leaf a b | Node a b [Tree a b] deriving (Show, Eq)

-- Every location in the tree is of some Chamber type.
data Chamber = Cavern |
               NarrowPassage |
               UndergroundRiver |
               SlipperyRocks deriving (Show, Eq)

-- An enemy has a name, an amount of damage that it deals
-- and an amount of gold that it drops (in that order).
data Enemy = Enemy String Integer Integer deriving (Show, Eq)

-- Gold n gives n amount of gold
-- Potion n heals n hp
data Loot = Gold Integer | Potion Integer deriving (Show, Eq)

-- An encounter is either a Fight with an Enemy, or a treasure where
-- you find Loot
data Encounter = Fight Enemy | Treasure Loot deriving (Show, Eq)

-- This is a type synonym for how we will represents our dungeons
type Dungeon = Tree Chamber [Encounter]

-- First argument is starting HP
-- Second argument is the dungeon map
-- Third argument is the path (each integer in the list shows what child
-- you descend into)
-- Calculate how much HP you have left and how much gold you've
-- accumulated after traversing the given path
traversePath :: Integer -> Dungeon -> [Int] -> (Integer, Integer)
traversePath hp (Leaf chamber encounters) [] =
    let (new_hp,new_gold) = myfoldl (hp,0) [ (health, reward)
                             | encounter <- encounters
                             , let (health, reward) = case encounter of
                                    Fight (Enemy _ damage gold) -> (-damage, gold)
                                    Treasure (Gold gold) -> (0, gold)
                                    Treasure (Potion potion_hp) -> (potion_hp, 0)
                            ]
    in (new_hp,new_gold)
traversePath hp (Node chamber encounters children) (x:xs) =
    let (new_hp,new_gold) = myfoldl (hp,0) [ (health, reward)
                             | encounter <- encounters
                             , let (health, reward) = case encounter of
                                    Fight (Enemy _ damage gold) -> (-damage, gold)
                                    Treasure (Gold gold) -> (0, gold)
                                    Treasure (Potion potion_hp) -> (potion_hp, 0)
                            ]
        hg@(h,g) = (traversePath new_hp (children !! x) xs)
    in (h,new_gold + g)

myfoldl :: (Integer, Integer) -> [(Integer, Integer)] -> (Integer, Integer)
myfoldl (hp, gold) lst = 
    let a = foldl (+) hp  [hpp | (hpp, _) <- lst]
        b = foldl (+) gold  [gld | (_, gld) <- lst]
    in (a,b)
-- First argument is starting HP
-- Second argument is dungeon map
-- Find which path down the tree yields the most gold for you
-- You cannot turn back, i.e. you'll find a non-branching path
-- You do not need to reach the bottom of the tree
-- Return how much gold you've accumulated
findMaximumGain :: Integer -> Dungeon -> Integer
findMaximumGain hp EmptyTree = 0
findMaximumGain hp (Leaf chamber encounters) =
    let (new_hp,new_gold) = myfoldl (hp,0) [ (health, reward)
                             | encounter <- encounters
                             , let (health, reward) = case encounter of
                                    Fight (Enemy _ damage gold) -> (-damage, gold)
                                    Treasure (Gold gold) -> (0, gold)
                                    Treasure (Potion potion_hp) -> (potion_hp, 0)
                            ]
    in if new_hp > 0 then new_gold else 0
findMaximumGain hp (Node chamber encounters children) = 
    let (new_hp,new_gold) = myfoldl (hp,0) [ (health, reward)
                             | encounter <- encounters
                             , let (health, reward) = case encounter of
                                    Fight (Enemy _ damage gold) -> (-damage, gold)
                                    Treasure (Gold gold) -> (0, gold)
                                    Treasure (Potion potion_hp) -> (potion_hp, 0)
                            ]
    in maximum [g + (findMaximumGain new_hp (children!!i))| i <- [0..length children-1], let g = if new_hp > 0 then new_gold else 0]
                                                        


-- First argument is starting HP
-- Second argument is the dungeon map
-- Remove paths that you cannot go thorugh with your starting HP. (By
-- removing nodes from tree).
-- Some internal nodes may become leafs during this process, make the
-- necessary changes in such a case.
findViablePaths :: Integer -> Dungeon -> Dungeon
findViablePaths hp EmptyTree = EmptyTree
findViablePaths hp (Leaf chamber encounters) =
    let (new_hp,new_gold) = myfoldl (hp,0) [ (health, reward)
                             | encounter <- encounters
                             , let (health, reward) = case encounter of
                                    Fight (Enemy _ damage gold) -> (-damage, gold)
                                    Treasure (Gold gold) -> (0, gold)
                                    Treasure (Potion potion_hp) -> (potion_hp, 0)
                            ]
    in if new_hp > 0 then Leaf chamber encounters else EmptyTree
findViablePaths hp node@(Node chamber encounters children) =
    let (new_hp,new_gold) = myfoldl (hp,0) [ (health, reward)
                             | encounter <- encounters
                             , let (health, reward) = case encounter of
                                    Fight (Enemy _ damage gold) -> (-damage, gold)
                                    Treasure (Gold gold) -> (0, gold)
                                    Treasure (Potion potion_hp) -> (potion_hp, 0)]
    in if new_hp <= 0 then EmptyTree else
        let tmp_newpath = [findViablePaths new_hp child| child<-children]
            new_path = [child | child <- tmp_newpath, child /= EmptyTree]
            in (if null new_path
                then Leaf chamber encounters
                else Node chamber encounters new_path)
        

-- First argument is starting HP
-- Second Argument is dungeon map
-- Find, among the viable paths in the tree (so the nodes you cannot
-- visit is already removed) the two most distant nodes, i.e. the two
-- nodes that are furthest awat from each other.
mostDistantPair :: Integer -> Dungeon -> (Integer, Dungeon)
mostDistantPair _ _ = (0, EmptyTree)

-- Find the subtree that has the highest total gold/damage ratio
-- Simply divide the total gold in the subtree by the total damage
-- in the subtree. You only take whole subtrees (i.e you can take a new
-- node as the root of your subtree, but you cannot remove nodes
-- below it). Note that the answer may be the whole tree.
mostEfficientSubtree :: Dungeon -> Dungeon
mostEfficientSubtree _ = EmptyTree
