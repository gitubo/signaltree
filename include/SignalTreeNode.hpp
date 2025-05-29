#pragma once

#include <memory> 
#include <atomic>

#define STATUS_BIT_IN_EXECUTION 0b00000010
#define STATUS_BIT_IS_ACTIVE    0b00000001

using Status = uint8_t;
using TaskId = uint32_t;

namespace signaltree {

    struct SignalTreeNode {
        private:
            bool is_signal_node_;
            TaskId task_id_;
//            std::atomic<Status> signal_status_;
            std::atomic<uint32_t> signal_counter_;
        
            // Pointers to child nodes. Using unique_ptr for automatic memory management.
            // They are now const unique_ptr to indicate they are set at construction.
            const std::unique_ptr<SignalTreeNode> left_;
            const std::unique_ptr<SignalTreeNode> right_;
        
        public:
            // Constructor

            SignalTreeNode(
                 std::unique_ptr<SignalTreeNode> left_child = nullptr,
                 std::unique_ptr<SignalTreeNode> right_child = nullptr)
                : is_signal_node_(false),
//                  signal_status_(0),
                  signal_counter_(0),
                  left_(std::move(left_child)),
                  right_(std::move(right_child))
            {}

            SignalTreeNode(uint32_t task_id_)
               : is_signal_node_(true),
                 task_id_(task_id_),
//                 signal_status_(0),
                 signal_counter_(0),
                 left_(nullptr),
                 right_(nullptr)
           {}
        
            // Getters
//            bool is_signal_node() const { return is_signal_node_; }
            SignalTreeNode* left() const { return left_.get(); }
            SignalTreeNode* right() const { return right_.get(); }

            inline TaskId get_task_id() const { return task_id_; }

            inline bool increment_signal_counter();
            inline bool decrement_signal_counter();
            inline bool reset_signal_counter();
            inline uint32_t get_signal_counter() const;

        
            // Setters/Getters for flags
            /*
            inline bool set_status_active();
            inline bool unset_status_active();
            inline bool is_status_active() const;

            inline bool set_status_in_execution();
            inline bool unset_status_is_execution();
            inline bool is_status_in_execution() const;
            */

            SignalTreeNode* select();
        
            // No copy constructor or assignment operator needed with unique_ptr for children,
            // as unique_ptr handles move semantics.
            SignalTreeNode(SignalTreeNode&&) = default;
            SignalTreeNode& operator=(SignalTreeNode&&) = default;

            // Destructor is implicitly handled by unique_ptr
            ~SignalTreeNode() = default;
    };

}