;---
; Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
; published by The Pragmatic Bookshelf.
; Copyrights apply to this code. It may not be used to create training material,
; courses, books, articles, and the like. Contact us if you are in doubt.
; We make no guarantees that this code is fit for any purpose.
; Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
;---

(def deposit)

(defn account-transactions [account-id]
   #{"1000" "1001" "1002"} )

(defn create-transaction [account, type, amount]
  (println account type amount)
  "1001"
  )

(defn account-open? [account-id]
  true)

;
(defn accept-deposit [account-id amount]
   { :pre [  (> amount 0.00) 
             (account-open? account-id) ]
     :post [ (contains? (account-transactions account-id) %) ] }
   "Accept a deposit and return the new transaction id"
   ;; Some other processing goes here...
   ;; Return the newly created transaction:
   (create-transaction account-id :deposit amount))
;

(accept-deposit "1001" 422.00) ; Ok
(accept-deposit "1002" -422.00) ; should blow up

