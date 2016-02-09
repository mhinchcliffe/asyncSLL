gfCheckValid=function(int UID1,int priority1,int value1,int UID2,int priority2,int value2)
	if (value1==value2)
		return false
	end
	if (math.abs(priority1-value1)==math.abs(priority2-value2))
		return false
	end

	return true
end
print("hey")
gsPurpose="this function is used to compare the position of two queens on a chessboard, and see if they can take one another in a single move. used to solve the nQueens problem"
