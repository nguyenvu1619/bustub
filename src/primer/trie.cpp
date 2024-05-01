#include "primer/trie.h"
#include <cstddef>
#include <memory>
#include <string_view>
#include "common/exception.h"

namespace bustub {

template <class T>
auto Trie::Get(std::string_view key) const -> const T * {

  // You should walk through the trie to find the node corresponding to the key. If the node doesn't exist, return
  // nullptr. After you find the node, you should use `dynamic_cast` to cast it to `const TrieNodeWithValue<T> *`. If
  // dynamic_cast returns `nullptr`, it means the type of the value is mismatched, and you should return nullptr.
  // Otherwise, return the value.
  auto node = root_;
  for (char i : key) {
    node = node->children_.at(i);
    if (node == nullptr) {
      return nullptr;
    }
  }
  if (node->is_value_node_) {
    auto *value_node = dynamic_cast<const TrieNodeWithValue<T> *>(node.get());
    return value_node == nullptr ? nullptr : value_node->value_.get();
  }
  return nullptr;
}

template <class T>
auto Trie::Put(std::string_view key, T value) const -> Trie {
  if(this->root_ == nullptr){
    return Trie(std::make_shared<TrieNodeWithValue<T>>(std::make_shared<T>(std::move(value))));
  }
  // Note that `T` might be a non-copyable type. Always use `std::move` when creating `shared_ptr` on that value.

  // You should walk through the trie and create new nodes if necessary. If the node corresponding to the key already
  // exists, you should create a new `TrieNodeWithValue`.
  auto new_trie = Trie((root_->Clone()));
  auto new_node = new_trie.root_->children_;
  auto node = root_->children_;
  for (char i : key) {
    if (node[i] == nullptr) {
      if(i != key.back()){
      new_node[i] = std::make_shared<TrieNode>(TrieNode());
      } else {
        new_node[i] = std::make_shared<TrieNodeWithValue<T>>(std::make_shared<T>(std::move(value)));
      }
      continue;
    }
    if(i == key.back()){
      new_node[i] = std::make_shared<TrieNodeWithValue<T>>(std::make_shared<T>(std::move(value)));
      continue;
    }
    new_node[i] = node[i]->Clone();
    node = node[i]->children_;
    new_node = new_node[i]->children_;
  }
  return new_trie;
}

auto Trie::Remove(std::string_view key) const -> Trie {
  
  auto new_trie = Trie((root_->Clone()));
  return new_trie;
  // auto new_node = new_trie.root_->children_;
  // auto node = root_->children_;
  // for (char i : key) {
  //   if (node[i] == nullptr) {
  //     return new_trie;
  //   }
  //   if(i == key.back()){
  //     if(node[i]->is_value_node_){
  //       new_node[i] = std::make_shared<TrieNode>(static_cast<std::unique_ptr<TrieNode>>(node[i]->Clone()));
  //     } else {
  //       if(node[i]->children_.empty()){
  //         new_node[i] = nullptr;
  //       }
  //     }
  //     continue;
  //   }
  //   new_node[i] = node[i]->Clone();
  //   node = node[i]->children_;
  //   new_node = new_node[i]->children_;
  // }
  // return new_trie;
  // You should walk through the trie and remove nodes if necessary. If the node doesn't contain a value any more,
  // you should convert it to `TrieNode`. If a node doesn't have children any more, you should remove it.
}

// Below are explicit instantiation of template functions.
//
// Generally people would write the implementation of template classes and functions in the header file. However, we
// separate the implementation into a .cpp file to make things clearer. In
// implementation of the template functions, we need to explicitly instantiate them here, so that they can be picked up
// by the linker.

template auto Trie::Put(std::string_view key, uint32_t value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const uint32_t *;

template auto Trie::Put(std::string_view key, uint64_t value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const uint64_t *;

template auto Trie::Put(std::string_view key, std::string value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const std::string *;

// If your solution cannot compile for non-copy tests, you can remove the below lines to get partial score.

using Integer = std::unique_ptr<uint32_t>;

template auto Trie::Put(std::string_view key, Integer value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const Integer *;

template auto Trie::Put(std::string_view key, MoveBlocked value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const MoveBlocked *;

}  // namespace bustub
