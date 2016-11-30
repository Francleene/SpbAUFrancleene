import Prelude hiding (lookup)

data BST k v = Nil
             | Node k v (BST k v) (BST k v)
             deriving (Show)

lookup :: Ord k => k -> BST k v -> Maybe v
lookup sk Nil = Nothing
lookup sk (Node k v l_BST r_BST)
    | sk < k  = lookup sk l_BST
    | sk == k = Just v
    | sk > k  = lookup sk r_BST

insert :: Ord k => k -> v -> BST k v -> BST k v
insert nk nv Nil = Node nk nv Nil Nil
insert nk nv (Node k v l_BST r_BST)
    | nk < k  = Node k v (insert nk nv l_BST) r_BST
    | nk == k = Node k nv l_BST r_BST
    | nk > k  = Node k v l_BST (insert nk nv r_BST)

merge :: Ord k => BST k v -> BST k v -> BST k v
merge Nil r_BST = r_BST
merge (Node fk fv fl_BST fr_BST) r_BST =
    Node fk fv fl_BST (merge fr_BST r_BST)

delete :: Ord k => k -> BST k v -> BST k v
delete dk Nil = Nil
delete dk (Node k v l_BST r_BST)
    | dk < k  = Node k v (delete dk l_BST) r_BST
    | dk == k = merge l_BST r_BST
    | dk > k  = Node k v l_BST (delete dk r_BST)
