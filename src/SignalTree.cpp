#include "SignalTree.hpp"


namespace signaltree {

    TaskId SignalTree::append_task(std::function<void()> callback) {
        tasks_.emplace_back(callback);
        return tasks_.size()-1;
    }

    void schedule_task(TaskId task_id) {
        //set_is_active();
    }

    SignalTreeReturnCode SignalTree::execute_next_task() {
        // Traverse the tree and get the first active signal
        SignalTreeNode* node;

        while(true){
            node = root_->select();
            // Reserve the signal
            if (node && node->decrement_signal_counter()) {
                // Invoke the task associated with the signal
                if (node->get_task_id() >= tasks_.size()) {
                    return SignalTreeReturnCode::OUT_OF_RANGE;
                }
                tasks_[node->get_task_id()].invoke();
            }
        }
        
        return SignalTreeReturnCode::SUCCESS;
    }

}