import re

def parse_total_pl(filename):
    total_pl_values = []
    
    with open(filename, 'r') as file:
        lines = file.readlines()
        
    for line in lines:
        match = re.search(r'Total P&L: \$(.*)', line)
        
        if match:
            total_pl_value = float(match.group(1).replace(',', '')) 
            total_pl_values.append(total_pl_value)
            
    return total_pl_values

if __name__ == "__main__":
    filename = "result.log"
    total_pl_values = parse_total_pl(filename)
    print("Total P&L values:", total_pl_values)