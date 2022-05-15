/// 1.) Search in bool CHARACTER::DoRefine(LPITEM item, bool bMoneyOnly):

	// END_OF_REFINE_COST

	if (prob <= prt->prob)
	{
		// 성공! 모든 아이템이 사라지고, 같은 속성의 다른 아이템 획득
		LPITEM pkNewItem = ITEM_MANAGER::instance().CreateItem(result_vnum, 1, 0, false);

// under, you have: if (pkNewItem)
	// well, in this 'if', search this:

			ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (REFINE SUCCESS)");
			// END_OF_DETAIL_REFINE_LOG

			pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, bCell)); 

// and replace this raw with this:

#ifdef ENABLE_STONES_STACKFIX
			DWORD dwStonesVnum = item->GetVnum();

			if (item->GetType() == ITEM_METIN) {
				item->SetCount(item->GetCount() - 1);
				pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, pos));
				ITEM_MANAGER::instance().FlushDelayedSave(pkNewItem);
			}
			else {
				ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (REFINE SUCCESS)");
				ITEM_MANAGER::instance().FlushDelayedSave(pkNewItem);
				pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, bCell)); 
			}
#else
			pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, bCell));
			ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (REFINE SUCCESS)");
#endif

/// 2.) Search in bool CHARACTER::DoRefineWithScroll(LPITEM item):

	if (prob <= success_prob)
	{
		// 성공! 모든 아이템이 사라지고, 같은 속성의 다른 아이템 획득
		LPITEM pkNewItem = ITEM_MANAGER::instance().CreateItem(result_vnum, 1, 0, false);

// under, you have: if (pkNewItem)
	// well, in this 'if', search this:

			ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (REFINE SUCCESS)");

			pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, bCell)); 

// and replace this raw with this:

#ifdef ENABLE_STONES_STACKFIX
			DWORD dwStonesVnum = item->GetVnum();

			if (item->GetType() == ITEM_METIN) {
				item->SetCount(item->GetCount() - 1);
				pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, pos));
				ITEM_MANAGER::instance().FlushDelayedSave(pkNewItem);
			}
			else {
				ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (REFINE SUCCESS)");
				ITEM_MANAGER::instance().FlushDelayedSave(pkNewItem);
				pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, bCell)); 
			}
#else
			pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, bCell));
			ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (REFINE SUCCESS)");
#endif

/// 3.) Search:

	else if (!bDestroyWhenFail && result_fail_vnum)
	{
		
		LPITEM pkNewItem = ITEM_MANAGER::instance().CreateItem(result_fail_vnum, 1, 0, false);

// under, you have: if (pkNewItem)
	// well, in this 'if', search this:

			ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (REFINE FAIL)");

			pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, bCell)); 

// and replace this raw with this:

#ifdef ENABLE_STONES_STACKFIX
			DWORD dwStonesVnum = item->GetVnum();

			if (item->GetType() == ITEM_METIN) {
				item->SetCount(item->GetCount() - 1);
				pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, pos));
				ITEM_MANAGER::instance().FlushDelayedSave(pkNewItem);
			}
			else {
				ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (REFINE FAIL)");
				ITEM_MANAGER::instance().FlushDelayedSave(pkNewItem);
				pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, bCell)); 
			}
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

/// 4.) Search:

bool CHARACTER::DoRefineWithScroll(LPITEM item)
{
	if (!CanHandleItem(true))
	{
		ClearRefineMode();
		return false;
	}
..

// and add under, this:

#ifdef ENABLE_STONES_STACKFIX
	DWORD pos = GetEmptyInventory(item->GetSize());

	if (-1 == pos){
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("소지하고 있는 아이템이 너무 많습니다."));
		return false;
	}
#endif

/// 4.) Search:

bool CHARACTER::DoRefine(LPITEM item, bool bMoneyOnly)
{
	if (!CanHandleItem(true))
	{
		ClearRefineMode();
		return false;
	}
..

// and add under, this:

#ifdef ENABLE_STONES_STACKFIX
	DWORD pos = GetEmptyInventory(item->GetSize());

	if (-1 == pos){
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("소지하고 있는 아이템이 너무 많습니다."));
		return false;
	}
#endif

/// 5.) in bool CHARACTER::DoRefine(LPITEM item, bool bMoneyOnly):
			// go to end function and search, this:
		
	else
	{
		// 실패! 모든 아이템이 사라짐.
		DBManager::instance().SendMoneyLog(MONEY_LOG_REFINE, item->GetVnum(), -cost);
		NotifyRefineFail(this, item, IsRefineThroughGuild() ? "GUILD" : "POWER");
		item->AttrLog();
		ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (REFINE FAIL)");

		//PointChange(POINT_GOLD, -cost);
		PayRefineFee(cost);
	}

	return true;
}

// replace with this:

	else
	{
		// 실패! 모든 아이템이 사라짐.
		DBManager::instance().SendMoneyLog(MONEY_LOG_REFINE, item->GetVnum(), -cost);
		NotifyRefineFail(this, item, IsRefineThroughGuild() ? "GUILD" : "POWER");
		item->AttrLog();
#ifdef ENABLE_STONES_STACKFIX
		item->SetCount(item->GetCount() - 1);
#else
		ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (REFINE FAIL)");
#endif

		//PointChange(POINT_GOLD, -cost);
		PayRefineFee(cost);
	}
