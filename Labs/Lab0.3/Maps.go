package main

import (
	"golang.org/x/tour/wc"
	"strings"
)

func WordCount(s string) map[string]int {
	m := make(map[string]int)
	St := strings.Fields(s)
	for i := range St{
		m[St[i]] += 1
	}
	return m
}

func main() {
	wc.Test(WordCount)

}

