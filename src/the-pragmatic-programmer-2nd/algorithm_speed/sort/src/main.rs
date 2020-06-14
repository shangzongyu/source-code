extern crate rand;
use rand::Rng;

type Element = u32;
type Elements = Vec<Element>;
type Sorter<T> = fn(&mut [T]) -> ();

///////////////////////////////////////////////////////////////
// Bubble Sort

pub mod bubble_sort {
    pub fn sort<T: Ord>(input: &mut [T]) {
        let size = input.len();

        for i in 0..(size) {
            for j in 0..(size - i - 1) {
                if input[j] > input[j + 1] {
                    input.swap(j, j + 1);
                }
            }
        }
    }
}

///////////////////////////////////////////////////////////////
// Insertion Sort

pub mod insertion_sort {
    pub fn sort<T: Ord>(input: &mut [T]) {
        for i in 1..input.len() {
            for j in (1..i + 1).rev() {
                if input[j - 1] <= input[j] {
                    break;
                }
                input.swap(j - 1, j)
            }
        }
    }
}

///////////////////////////////////////////////////////////////
// Selection Sort

pub mod selection_sort {
    pub fn sort<T: Ord>(input: &mut [T]) {
        for i in 0..input.len() {
            let mut small = i;
            for j in (i + 1)..input.len() {
                if input[j] < input[small] {
                    small = j;
                }
            }
            input.swap(small, i);
        }
    }
}

///////////////////////////////////////////////////////////////
// Quicksort

pub mod quicksort {
    fn partition<T: Ord>(input: &mut [T]) -> (&mut [T], &mut [T]) {
        let mut right = input.len() - 1;
        let mut left = 1;
        let pivot = 0;

        loop {
            while left <= right && input[left] < input[pivot] {
                left = left + 1;
            }

            while right >= left && input[right] >= input[pivot] {
                right = right - 1
            }
            if left > right {
                break ();
            }

            input.swap(left, right);
        }

        input.swap(0, right);
        let (low, rest) = input.split_at_mut(right);
        let (_, high) = rest.split_at_mut(1);
        (low, high)
    }

    pub fn sort<T: Ord>(input: &mut [T]) {
        match input.len() {
            0 => (),
            1 => (),
            _ => {
                let (low, high) = partition(input);
                sort(low);
                sort(high);
            }
        }
    }
}

///////////////////////////////////////////////////////////////
// helpers

fn create_vector_to_sort(size: u32) -> Elements {
    let mut result: Elements = Vec::with_capacity(size as usize);
    let mut rng = rand::thread_rng();

    for _i in 0..size {
        result.push(rng.gen());
    }
    result
}

fn time_func<F>(func: F, size: u32) -> u128
where
    F: Fn(&mut [Element]) -> (),
{
    let mut vector = create_vector_to_sort(size);
    let s1 = std::time::Instant::now();
    func(&mut vector[..]);
    let t1 = s1.elapsed().as_millis();
    t1
}

///////////////////////////////////////////////////////////////
// main program

fn main() {
    let example_sorts: [(&str, Sorter<u32>, u32); 4] = [
        ("Bubble Sort",    bubble_sort::sort,     10000),
        ("Insertion Sort", insertion_sort::sort,  10000),
        ("Selection Sort", selection_sort::sort,  10000),
        ("Quicksort",      quicksort::sort,     1000000),
    ];

    for (name, func, scale_factor) in example_sorts.iter() {
        println!("Using {}", name);
        for size in 1..12 {
            let scaled_size = size * scale_factor;
            let e1 = time_func(func, scaled_size);
            println!("{}, {}", scaled_size, e1);
        }
    }

}

///////////////////////////////////////////////////////////////
// Tests

#[cfg(test)]
mod test {
    const SORTING_FUNCTIONS: [super::Sorter<i32>; 4] = [
        super::bubble_sort::sort,
        super::insertion_sort::sort,
        super::selection_sort::sort,
        super::quicksort::sort,
    ];

    #[test]
    fn test_empty_array() {
        for do_sort in SORTING_FUNCTIONS.iter() {
            let mut input = [];
            do_sort(&mut input);
            assert_eq!(input, [])
        }
    }

    #[test]
    fn test_one_element_array() {
        for do_sort in SORTING_FUNCTIONS.iter() {
            let mut input = [999];
            do_sort(&mut input);
            assert_eq!(input, [999]);
        }
    }

    #[test]
    fn test_two_element_array_already_sorted() {
        for do_sort in SORTING_FUNCTIONS.iter() {
            let mut input = [9, 99];
            do_sort(&mut input);
            assert_eq!(input, [9, 99]);
        }
    }

    #[test]
    fn test_two_element_array_unsorted() {
        for do_sort in SORTING_FUNCTIONS.iter() {
            let mut input = [99, 9];
            do_sort(&mut input);
            assert_eq!(input, [9, 99]);
        }
    }

    #[test]
    fn test_two_element_array_same_values() {
        for do_sort in SORTING_FUNCTIONS.iter() {
            let mut input = [9, 9];
            do_sort(&mut input);
            assert_eq!(input, [9, 9]);
        }
    }

    const PERMS: [[i32; 3]; 6] = [
        [1, 2, 3],
        [1, 3, 2],
        [2, 1, 3],
        [2, 3, 1],
        [3, 1, 2],
        [3, 2, 1],
    ];
    #[test]
    fn test_ordering_combinations_of_three_values() {
        for do_sort in SORTING_FUNCTIONS.iter() {
            for perm in PERMS.iter() {
                let mut input = perm.clone();
                let mut expected = perm.clone();
                expected.sort();
                do_sort(&mut input);
                assert_eq!(input, expected);
            }
        }
    }

    #[test]
    fn test_8_element_vec() {
        for do_sort in SORTING_FUNCTIONS.iter() {
            let mut input = [88, 1, -3, 1234, 0, 1, 44, -999];
            let mut expected = input.clone();
            expected.sort();
            do_sort(&mut input);
            assert_eq!(input, expected);
        }
    }
}
