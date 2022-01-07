/// 1.) Search in bool CHARACTER::DoRefine(LPITEM item, bool bMoneyOnly):

	// END_OF_REFINE_COST

	if (prob <= prt->prob)
	{
		// 성공! 모든 아이템이 사라지고, 같은 속성의 다른 아이템 획득
		LPITEM pkNewItem = ITEM_MANAGER::instance().CreateItem(result_vnum, 1, 0, false);

// and add under, this:

#ifdef ENABLE_STONES_STACKFIX
		DWORD pos = GetEmptyInventory(item->GetSize());

		if (-1 == pos)
		{
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You don't have enough inventory space."));
			return false;
		}
#endif

// under, you have: if (pkNewItem)
	// well, in this 'if', search this:

			ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (REFINE SUCCESS)");
			// END_OF_DETAIL_REFINE_LOG

			pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, bCell)); 

// and replace this raw with this:

#ifdef ENABLE_STONES_STACKFIX
			DWORD dwItemVnum = item->GetVnum();

			if (item->GetVnum() >= 28000 && item->GetVnum() <= 29000) {
				pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, pos));
				ITEM_MANAGER::instance().FlushDelayedSave(pkNewItem);
			}

			item->SetCount(item->GetCount() - 1);
#else
			pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, bCell));
			ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (REFINE SUCCESS)");
#endif

/// 2.) Search in bool CHARACTER::DoRefineWithScroll(LPITEM item):

	if (prob <= success_prob)
	{
		// 성공! 모든 아이템이 사라지고, 같은 속성의 다른 아이템 획득
		LPITEM pkNewItem = ITEM_MANAGER::instance().CreateItem(result_vnum, 1, 0, false);

// and add under, this:

#ifdef ENABLE_STONES_STACKFIX
		DWORD pos = GetEmptyInventory(item->GetSize());

		if (-1 == pos)
		{
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You don't have enough inventory space."));
			return false;
		}
#endif

// under, you have: if (pkNewItem)
	// well, in this 'if', search this:

			ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (REFINE SUCCESS)");

			pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, bCell)); 

// and replace this raw with this:

#ifdef ENABLE_STONES_STACKFIX
			DWORD dwItemVnum = item->GetVnum();

			if (item->GetVnum() >= 28000 && item->GetVnum() <= 29000) {
				pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, pos));
				ITEM_MANAGER::instance().FlushDelayedSave(pkNewItem);
			}

			item->SetCount(item->GetCount() - 1);
#else
			pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, bCell));
			ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (REFINE SUCCESS)");
#endif

/// 3.) Search::

	else if (!bDestroyWhenFail && result_fail_vnum)
	{
		
		LPITEM pkNewItem = ITEM_MANAGER::instance().CreateItem(result_fail_vnum, 1, 0, false);

// and add under, this:

#ifdef ENABLE_STONES_STACKFIX
		DWORD pos = GetEmptyInventory(item->GetSize());

		if (-1 == pos)
		{
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You don't have enough inventory space."));
			return false;
		}
#endif

// under, you have: if (pkNewItem)
	// well, in this 'if', search this:

			ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (REFINE FAIL)");

			pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, bCell)); 

// and replace this raw with this:

#ifdef ENABLE_STONES_STACKFIX
			DWORD dwItemVnum = item->GetVnum();

			if (item->GetVnum() >= 28000 && item->GetVnum() <= 29000) {
				pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, pos));
				ITEM_MANAGER::instance().FlushDelayedSave(pkNewItem);
			}

			item->SetCount(item->GetCount() - 1);
#else
			pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, bCell));
			ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (REFINE FAIL)");
#endif

// search:

						ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (METIN)");

// and replace with this:

#ifdef ENABLE_STONES_STACKFIX
						item->SetCount(item->GetCount() - 1);
#else
						ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (METIN)");
#endif

