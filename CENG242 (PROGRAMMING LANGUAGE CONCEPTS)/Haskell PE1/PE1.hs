module PE1 where

import Text.Printf

-- PE1: Recipe Calculator
-- The premise of this homework if to write a recipe calculator that
-- calculates: how much a recipe costs to make, what can be made with the
-- ingredients already available, and how much extra ingredients need to
-- be bought in order to make a recipe.

-- Recipe = Recipe Name [(Ingredient, Quantity)]
data Recipe = Recipe String [(String, Double)] deriving Show

-- Price = Price Ingredient Quantity Price
data Price = Price String Double Double deriving Show

-- You can use this as-is
getRounded :: Double -> Double 
getRounded x = read s :: Double
               where s = printf "%.2f" x

-- Calculate how much the given amount of the given ingredient costs
getIngredientCost :: (String, Double) -> [Price] -> Double
getIngredientCost (ingredient,quantity) price_list = head [getRounded (quantity*(p2 / p1)) | p@(Price i p1 p2) <- price_list, i==ingredient]


-- Calculate how much it costs to buy all the ingredients of a recipe
recipeCost :: Recipe -> [Price] -> Double
recipeCost (Recipe recipe_name ingredients) price_list = getRounded (sum [(getIngredientCost x price_list) | x <- ingredients])

-- Given a list of how much you already have of each ingredient,
-- calculate how much of which ingredients are missing for a recipe
missingIngredients :: Recipe -> [(String, Double)] -> [(String, Double)]
missingIngredients (Recipe recipe_name ingredients) stock = [(name, getRounded amnt) | ingredient <-ingredients,let (name, amnt) = checkStockForOneIngredient ingredient stock,
                                                  amnt > 0]

checkStockForOneIngredient :: (String, Double) -> [(String, Double)] ->(String, Double)
checkStockForOneIngredient  (ingr_name, needed_amnt) stock = 
    let k = [ (ingr_name, needed_amnt -amnt) | x@(name , amnt) <- stock , ingr_name == name]
    in if null k then (ingr_name, needed_amnt) else (head k)

-- Given a list of ingredients in your kitchen, calculate what you would
-- have left after making the given recipe. If there isn't enough of an
-- ingredient, the recipe cannot be made! You shouldn't change the amount
-- of ingredient in that case.
makeRecipe :: [(String, Double)] -> Recipe -> [(String, Double)]
makeRecipe stock recipe@((Recipe recipe_name ingredients)) = 
    let missing = missingIngredients recipe stock
    in if null missing then  
        let used = [name | (name, amnt) <- stock, (ingr_name, needed_amnt) <- ingredients, ingr_name == name]
            remaining = [(name,getRounded (amnt - needed_amnt)) | (name, amnt) <- stock, (ingr_name, needed_amnt) <- ingredients, ingr_name == name] ++ [(name, getRounded amnt) | (name, amnt) <- stock, notElem name used]
        in remaining
    else stock



-- Given a list of ingredients you already have, and a list of recipes,
-- make a shopping list showing how much of each ingredient you need
-- to buy, and its cost. Each ingredient mush appear in the shopping list
-- at most once (no duplicates!).

makeShoppingList :: [(String, Double)] -> [Recipe] -> [Price] -> [(String, Double, Double)]
makeShoppingList stock recipes price_list = 
    let new_stock = foldl makeRecipe2 stock [r|r@(Recipe recipe_name ingredients) <- recipes]
        shopping_list_with_dup = [(x,-y)|(x,y)<-new_stock,y<0]
        shopping_list = removeDuplicates shopping_list_with_dup
    in [(name,amnt,getIngredientCost (name, amnt) price_list)|(name,amnt)<-shopping_list]

makeRecipe2 :: [(String, Double)] -> Recipe -> [(String, Double)]
makeRecipe2 stock recipe@((Recipe recipe_name ingredients)) = 
    let missing = missingIngredients recipe stock
        remaining = [(name, amnt - needed_amnt) | (name, amnt) <- stock, (ingr_name, needed_amnt) <- ingredients, ingr_name == name]
        used = [name | (name, amnt) <- stock, (ingr_name, needed_amnt) <- ingredients, ingr_name == name]
    in if null missing then  
        let remaining2 = remaining  ++ [(name, amnt) | (name, amnt) <- stock, notElem name used]
        in remaining2
    else remaining ++ [(name,-amnt)|(name,amnt)<-missing] ++  [(name, amnt) | (name, amnt) <- stock, notElem name used]

removeDuplicates :: [(String, Double)] -> [(String, Double)]
removeDuplicates [] = []
removeDuplicates (x:xs) = x : removeDuplicates (filter (/=x) xs)
