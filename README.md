# HuffmanCodeGenerator

Finds the shortest path between two vertices by implementing an undirected weighted Graph ADT and performing **Dijkstra's Algorithm**.

## Design 

* [x] Generates a list of the frequency in which characters appear in the string using a map.
* [x] Inserts the characters and their frequencies into a priority queue (sorted first by the lowest frequency and then lexicographically).
* [x] Removes two characters/frequencies pairs from the priority queue and turns them into leaf nodes on a binary tree.
* [x] An intermediate node was created to be their parent using the sum of the frequencies for those children. It is inserted back in the priority queue.
* [x] The last pair in the priority queue is the root node of the tree.
* [x] Using this new tree,the characters in the string are encoded using a map with their prefix code by traversing the tree to find where the character’s leaf is. When traversal goes left, it adds a 0 to the code, when it goes right, it adds a 1 to the code.
* [x] The characters in the string are replaced with their new variable-length prefix codes.

## Codes for the characters

<img width="682" alt="Screenshot 2022-12-20 at 11 38 48 PM" src="https://user-images.githubusercontent.com/95254925/208822582-08c40cbf-c48e-4f1f-8b2f-dac7863c64a6.png">

## License

    Copyright [Juliana El Rayes]

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
