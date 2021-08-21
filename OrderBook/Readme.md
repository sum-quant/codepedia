Liquidbook will notify the application when significant events occur to allow the application to actually execute the trades identified by Liquibook, and to allow the application to publish market data for use by traders.

The notifications generated include:

Notifications intended for trader submitting an order:
Order accepted
Order rejected
Order filled (full or partial)
Order replaced
Replace request rejected
Order canceled
Cancel request rejected.
Notifications intended to be published as Market Data
Trade
Note this should also trigger the application to do what it needs to do to make the trade happen.
Security changed
Triggered by any event that effects a security
Does not include rejected requests.
Notification of changes in the depth book (if enabled)
Depth book changed
Best Bid or Best Offer (BBO) changed.


Design :

Unordered _map datastructure to maintain the order_ID based on hash details , bucket consits of map of orders to maintain price and quantity based on the priority of price-time.
.
Add -O(1)+ log(n) in Map.

Delete/Reject -0(1)+ log(n) erase in Map.

Modify -o(1)

Input is order.csv file 

Output generates lmit order_book.
