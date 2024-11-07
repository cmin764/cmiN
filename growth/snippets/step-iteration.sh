#! /usr/bin/env bash

# Define an associative array (dictionary)
declare -A step_outcomes

# Manually set the step outcomes here for demonstration purposes
# In practice, these values are dynamically retrieved from step results
step_outcomes["step1"]="success"
step_outcomes["step2"]="failure"
step_outcomes["step3"]="success"

#echo $step_outcomes

succeeded=0
failed=0

# Iterate over the dictionary and process the outcomes
for step_id in ${!step_outcomes[@]}; do
  outcome=${step_outcomes[$step_id]}
#  echo $outcome

  if [[ "$outcome" == "success" ]]; then
    echo "✅ $step_id succeeded"
    succeeded=$((succeeded + 1))  # Increment succeeded count
  else
    echo "❌ $step_id failed"
    failed=$((failed + 1))  # Increment failed count
  fi
done

# Output the results
echo "Succeeded: $succeeded"
echo "Failed: $failed"
