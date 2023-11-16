## HTA
0. Order Food as a group
	1. Selecting group of friends
		2. Select a "host" for delivery
		3. Make group order available to other members of the group
	2. Selecting Food Vendor
		1. Narrow down available vendor options based on group's preferences (eg. time to delivery, type of food, etc)
		2. vote on viable options to determine final 
	3. Selecting Menu Items 
		1. Each member gains access to the menu of the selected vendor
		2. users browse and select their order based on preferences or dietary restrictions
		3. Place group food order
	4. Payment of food items
		1. Determine each users share of total cost, taking into account food cost and additional charges
		2. Collect share of cost from each member of the group
		3. Pay vendor
	5. Vendor Order Handling
		1. Vendor receives order from group
		2. Vendor makes and packages food
			1. while packaging, labelling/organising containers based on who ordered what (eg. numbers on boxes which are assigned to each person's portion of an order)
	6. Delivery and distribution of food items
		1. Delivery delivered to "host"
		2. any outstanding payment owed is reconciled
		3. food items are distributed among hungry group members

## Analysis
Each task is done in sequential order and, with the exception of task 4, must be completed in order for the next task to continue. Task 4, the payment step, can in some cases be completed upon delivery, hence step 6.2 being a reconciliation of any payment due. This is generally limited to cash transactions. The payment step can also be a cause of some friction, because in the event of a member of the group being unable to pay for their portion, other users can choose to cover a portion or all of that members payment due, or alternatively remove their portion of the order entirely. Additionally, this analysis focuses on the user side of the interaction, rather than the vendor or delivery personnel side. As a result, edge cases such as vendors choosing not to fill an order, or a shortage of delivery personnel resulting in an order being unfilled, not being considered in the analysis above. It is important to consider these cases as there is an added level of complexity in terms of returning money paid to each member of the group and organising another order if needed. 