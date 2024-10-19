#ifndef SUBSCRIPTIONLIST_H
#define SUBSCRIPTIONLIST_H

#include <vector>
#include <memory>
#include "Subscription.h"

template <typename T>
class SubscriptionList {
private:
    std::vector<std::shared_ptr<T>> subscriptions;

public:
    void addSubscription(const std::shared_ptr<T>& subscription) {
        subscriptions.push_back(subscription);
    }

    void displayAll() const {
        for (const auto& sub : subscriptions) {
            sub->display();
        }
    }

   
};

#endif
