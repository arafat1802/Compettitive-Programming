def left_edge_placement(cell_widths, chip_width):
    # Sort the cell widths in decreasing order
    sorted_cells = sorted(cell_widths, reverse=True)
    
    # Initialize an empty row for placement
    row = [(0, 0)]  # Each tuple represents (cell_left, cell_right)

    placements = {}  # Dictionary to store placements of cells

    for cell_width in sorted_cells:
        placed = False
        
        for i, (cell_left, cell_right) in enumerate(row):
            if cell_right + cell_width <= chip_width:
                # Place the cell in the current row
                cell_position = (cell_right, cell_right + cell_width)
                placements[f'Cell{len(placements) + 1}'] = cell_position
                row[i] = cell_position
                
                # Update the flag to indicate successful placement
                placed = True
                break
        
        if not placed:
            # If the cell doesn't fit in any row, create a new row
            row.append((0, cell_width))
            placements[f'Cell{len(placements) + 1}'] = (0, cell_width)
    
    return placements

# Example usage:
if __name__ == "__main__":
    cell_widths = [4, 5, 2, 3, 6, 2]
    chip_width = 10

    placements = left_edge_placement(cell_widths, chip_width)
    for cell, position in placements.items():
        cell_name = cell
        left_edge, right_edge = position
        print(f"{cell_name}: Left edge at {left_edge}, Right edge at {right_edge}")