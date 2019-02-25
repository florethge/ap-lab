package main

import (
	"fmt"
	"log"
	"os"
	"path/filepath"
)

func main() {
	var root string
	if len(os.Args) == 1 {
		log.Fatal("No path given, Please specify path.")
		return
	}
	if root = os.Args[1]; root == "" {
		log.Fatal("No path given, Please specify path.")
		return
	}
	fmt.Printf("Path File: %v\n", os.Args[1])
	// filepath.Walk
	files, err := FilePathWalkDir(root)
	if err != nil {
		panic(err)
	}
	fmt.Printf("Directories = %d\n", len(files))

}
func FilePathWalkDir(root string) ([]string, error) {
	var files []string
	SLink := 0
	Other := 0

	err := filepath.Walk(root, func(path string, info os.FileInfo, err error) error {
		if !info.IsDir() {
			files = append(files, path)
		}
		if info.Mode()&os.ModeSymlink != 0 {
			SLink++
		}

		if info.Mode().IsRegular() {
			Other++
		}
		return nil
	})
	fmt.Println("Sym Link = ", SLink)
	fmt.Println("Others = ", Other)
	return files, err
}
