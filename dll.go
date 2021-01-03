package main

import (
	"fmt"
)

// DLLNode is the doubly linked list for *TreeNode children
type DLLNode struct {
	data *TreeNode
	len int
	prev, next *DLLNode
}

// Append appends a *TreeNode to the list
func(node *DLLNode) Append(n *TreeNode) {
	if node.len == 0 {
		node.data = n
		node.len = 1
		return
	} else if node.next == nil {
		node.len++
		node.next = &DLLNode{
			data: n,
			len: 1,
			prev: node,
		}
		return
	}
	node.len++
	node.next.Append(n)
}

// Delete deletes a node given a *TreeNode or name of of *TreeNode
func(node *DLLNode) Delete(data interface{}) (n *TreeNode, err error) {
	switch data.(type) {
	case *TreeNode:
		if node.data == data.(*TreeNode) {
			n = node.data
		}
		n, err = node.next.Delete(data)
	case string:
		if node.data.name == data.(string) {
			n = node.data
		}
		n, err = node.next.Delete(data)
	default:
		err = fmt.Errorf("invalid data type")
	}
	return
}

// Find returns the node containing a *TreeNode with a given name
func(node *DLLNode) Find(name string) *TreeNode {
	if node.data.name != name {
		if node.next == nil {
			return nil
		}
		return node.next.Find(name)
	}
	return node.data
}

// ToArray returns an array representation of the list
func(node *DLLNode) ToArray() (arr []*TreeNode) {
	if node.len == 0 {
		return
	}
	arr = make([]*TreeNode, node.len)
	n := node
	for i := 0; i < node.len; i++ {
		arr[i] = n.data
		n = n.next
	}
	return
}

// ToMap returns a map representation of the list with the names of the
// *TreeNode as the keys and the *TreeNode as the value
func(node *DLLNode) ToMap() (m map[string]*TreeNode) {
	if node.len == 0 {
		return
	}
	m = make(map[string]*TreeNode)
	n := node
	for i := 0; i < node.len; i++ {
		m[n.data.name] = n.data
		n = n.next
	}
	return
}

// GetHead returns the head of the linked list
func(node *DLLNode) GetHead() *DLLNode {
	if node.prev == nil {
		return node
	}
	return node.prev.GetHead()
}
