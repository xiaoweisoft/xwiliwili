//
// Created by fang on 2022/8/2.
//

#include <borealis/core/thread.hpp>

#include "fragment/search_tab.hpp"
#include "fragment/search_order.hpp"
#include "fragment/search_bangumi.hpp"
#include "fragment/search_cinema.hpp"
#include "fragment/search_hots.hpp"
#include "fragment/search_history.hpp"
#include "utils/shortcut_helper.hpp"

SearchTab::SearchTab() {
    this->inflateFromXMLRes("xml/fragment/search_tab.xml");
    brls::Logger::debug("Fragment SearchTab: create");

    this->registerAction(
        "上一项", brls::ControllerButton::BUTTON_LB,
        [this](brls::View* view) -> bool {
            tabFrame->focus2LastTab();
            return true;
        },
        true);

    this->registerAction(
        ShortcutHelper::getLast(),
        [this](brls::View* view) -> bool {
            tabFrame->focus2LastTab();
            return true;
        });

    this->registerAction(
        "下一项", brls::ControllerButton::BUTTON_RB,
        [this](brls::View* view) -> bool {
            tabFrame->focus2NextTab();
            return true;
        },
        true);

    this->registerAction(
    ShortcutHelper::getNext(),
        [this](brls::View* view) -> bool {
            tabFrame->focus2NextTab();
            return true;
        });
}

SearchTab::~SearchTab() { brls::Logger::debug("Fragment SearchTabActivity: delete"); }

brls::View* SearchTab::create() { return new SearchTab(); }

void SearchTab::focusNthTab(int i) { this->tabFrame->focusTab(i); }

void SearchTab::setTabBarVisibility(bool visible) {
    auto vis = visible ? brls::Visibility::VISIBLE : brls::Visibility::GONE;
    this->tabFrame->getView("auto_tab_frame/auto_sidebar")->setVisibility(vis);
    // Also hide the sub-tabs (sort order) within the video tab
    this->searchVideoTab->setTabBarVisibility(visible);
    // Restore top spacing lost from hiding the tab bar
    if (!visible) this->setPaddingTop(15);
}

SearchHistory* SearchTab::getSearchHistoryTab() { return searchHistoryTab; };

SearchHots* SearchTab::getSearchHotsTab() { return searchHotsTab; }

SearchOrder* SearchTab::getSearchVideoTab() { return searchVideoTab; }

SearchBangumi* SearchTab::getSearchBangumiTab() { return searchBangumiTab; }

SearchCinema* SearchTab::getSearchCinemaTab() { return searchCinemaTab; }
