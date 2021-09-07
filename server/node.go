package main

import (
  "encoding/json"
  "io/ioutil"
)

type Node struct {
  // The network address of the node
  Addr string `json:"addr"`
  // The network addresses of the other nodes the current node knows about
  KnownPeers []string `json:"knownPeers"`
  // The node structures that are mapped to KnownPeers
  // Therefore, KnownPeers[i] == knownNodes[i].Addr
  // Not exported as it shouldn't be added to the JSON
  knownNodes []*Node
  // The directories (roots) that the Node holds/keeps track of, if any
  Holds []string `json:"holds"`
}

// LoadNode returns a node from the a json file
func LoadNode() (*Node, error) {
  data, err := ioutil.ReadFile("node_state.json")
  if err != nil {
    return nil, err
  }
  var n *Node
  return n, json.Unmarshal(n)
}

// FindHolder returns the address of a node that holds the data of the argument
// passed, if one exists
func FindHolder(name string) (string, error) {
  /* TODO: Try using RPC */
  return "", nil
}

// SaveNode saves the current node to a json file
func (n *Node) SaveNode() error {
  /* TODO: Save state to a file passed thru a config */
  data, err := n.ToJSON()
  if err == nil {
    err = ioutil.WriteFile("node_state.json", data, 0755)
  }
  return err
}

// ToJSON returns the json bytes of the node
func (n *Node) ToJSON() ([]byte, error) {
  return json.Marshal(n)
}

// ToJSONString returns the stringified json data of the node
func (n *Node) ToJSONString() (string, error) {
  b, err := n.ToJSON()
  return string(b), err
}
