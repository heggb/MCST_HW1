import subprocess
import os
import sys
import time
from termcolor import cprint, colored

TEST_DIRS = {
    "1": "task_tests/task1_graph/tests",
    "2": "task_tests/task2_dijkstra/tests",
    "3": "task_tests/task3_maxflow/tests",
    "4": "task_tests/task4_tarjan/tests"
}

BINARIES = {
    "1": "build/solution",
    "2": "build/solution",
    "3": "build/solution",
    "4": "build/solution"
}

def parse_test(file_path):
    input_lines, expected_lines = [], []
    with open(file_path) as f:
        for line in f:
            if line.startswith('+'):
                input_lines.append(line[1:].strip())
            elif line.startswith('-'):
                expected_lines.append(line[1:].strip())
    return input_lines, expected_lines

def run_test(binary, test_file):
    name = os.path.basename(test_file)
    inputs, expected_outputs = parse_test(test_file)

    try:
        process = subprocess.Popen(
            [f'./{binary}'],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )

        start = time.time()
        stdout, stderr = process.communicate(input='\n'.join(inputs) + '\n', timeout=2)
        end = time.time()

        actual_lines = stdout.strip().split('\n')
        success = True
        for i, expected in enumerate(expected_outputs):
            if i >= len(actual_lines) or actual_lines[i].strip() != expected:
                print(f"\n{name}: MISMATCH")
                print("Input:")
                for l in inputs:
                    print("> " + l)
                print(f"\nExpected line {i+1}: {expected}")
                if i < len(actual_lines):
                    print(f"Got line {i+1}     : {actual_lines[i]}")
                else:
                    print(f"Got line {i+1}     : <no output>")
                success = False
                break

        if success:
            elapsed = (end - start) * 1000
            print(f"{name}: OK ({elapsed:.1f} ms)")
        return success

    except subprocess.TimeoutExpired:
        process.kill()
        print(f"{name}: TIMEOUT")
        return False

def run_all(task_number=None):
    total = 0
    passed = 0
    tasks = [task_number] if task_number else ["1", "2", "3", "4"]

    for task in tasks:
        binary = BINARIES[task]
        test_dir = TEST_DIRS[task]
        if not os.path.isfile(binary):
            cprint(f"⚠️  Binary '{binary}' not found. Skipping tests for task {task}.", "yellow")
            continue
        cprint(f"\n== Testing Task {task} ==\n", "cyan")
        for test_file in sorted(os.listdir(test_dir)):
            if test_file.endswith(".txt"):
                total += 1
                full_path = os.path.join(test_dir, test_file)
                if run_test(binary, full_path):
                    passed += 1

    print()
    if passed == total:
        cprint(f"✅ All {total} tests passed", "green")
    else:
        cprint(f"❌ {total - passed} of {total} tests failed", "red")

if __name__ == '__main__':
    if len(sys.argv) > 1:
        run_all(sys.argv[1])
    else:
        run_all()