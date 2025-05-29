#include "SignalTreeNode.hpp"


namespace signaltree {

    SignalTreeNode* SignalTreeNode::select() {
        return nullptr;
    }

    /*
    // STATUS_BIT_IS_ACTIVE
    inline bool SignalTreeNode::set_status_active() {
        // Load status value and evaluate if it is already set, in case return false
        Status expected = signal_status_.load(std::memory_order_relaxed);
        if (expected & STATUS_BIT_IS_ACTIVE) { return false; }
        
        // Evaluate desired status and use compare_exchange_weak to set it
        // If the exchange fails, it means another thread has already modified the status
        Status desired = expected | STATUS_BIT_IS_ACTIVE;
        return signal_status_.compare_exchange_weak(expected, desired, std::memory_order_relaxed);
     }
    
     inline bool SignalTreeNode::unset_status_active() {
        // Load status value and evaluate if it is already unset, in case return false
        Status expected = signal_status_.load(std::memory_order_relaxed);
        if (!(expected & STATUS_BIT_IS_ACTIVE)) { return false; }
        
        // Evaluate desired status and use compare_exchange_weak to unset it
        // If the exchange fails, it means another thread has already modified the status
        Status desired = expected & ~STATUS_BIT_IS_ACTIVE;
        return signal_status_.compare_exchange_weak(expected, desired, std::memory_order_relaxed);
    }

    inline bool SignalTreeNode::is_status_active() const {
        return signal_status_.load() & STATUS_BIT_IS_ACTIVE;
    }

    // STATUS_BIT_IN_EXECUTION
    inline bool SignalTreeNode::set_status_in_execution() {
        // Load status value and evaluate if it is already set, in case return false
        Status expected = signal_status_.load(std::memory_order_relaxed);
        if (expected & STATUS_BIT_IN_EXECUTION) { return false; }
        
        // Evaluate desired status and use compare_exchange_weak to set it
        // If the exchange fails, it means another thread has already set the status
        Status desired = expected | STATUS_BIT_IN_EXECUTION;
        return signal_status_.compare_exchange_weak(expected, desired, std::memory_order_relaxed);
    }
    
    inline bool SignalTreeNode::unset_status_is_execution() {
        // Load status value and evaluate if it is already unset, in case return false
        Status expected = signal_status_.load(std::memory_order_relaxed);
        if (!(expected & STATUS_BIT_IN_EXECUTION)) { return false; }
        
        // Evaluate desired status and use compare_exchange_weak to unset it
        // If the exchange fails, it means another thread has already modified the status
        Status desired = expected & ~STATUS_BIT_IN_EXECUTION;
        return signal_status_.compare_exchange_weak(expected, desired, std::memory_order_relaxed);
    }

    inline bool SignalTreeNode::is_status_in_execution() const {
        return signal_status_.load() & STATUS_BIT_IN_EXECUTION;
    }
    */

    // SIGNAL_COUNTER
    inline uint32_t SignalTreeNode::get_signal_counter() const { 
        return signal_counter_.load(std::memory_order_relaxed); 
    }

    inline bool SignalTreeNode::increment_signal_counter() {
        uint32_t expected = signal_counter_.load(std::memory_order_relaxed);
        
        if (!expected) { return false; }
        
        uint32_t desired = expected + 1;
        return signal_counter_.compare_exchange_weak(expected, desired, std::memory_order_relaxed);
    }

    inline bool SignalTreeNode::decrement_signal_counter() {
        uint32_t expected = signal_counter_.load(std::memory_order_relaxed);
        
        if (!expected) { return false; }
        
        uint32_t desired = expected - 1;
        return signal_counter_.compare_exchange_weak(expected, desired, std::memory_order_relaxed);
    }

}