import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file
df = pd.read_csv("Example3.csv")

# Create the plot
plt.figure(figsize=(32, 6))

# Get all column names
all_columns = df.columns.tolist()

# First column is always time (x-axis)
time_column = all_columns[0]

# All other columns are agent columns to plot
agent_columns = all_columns[1:]

# Plot each agent as a separate line
for column in agent_columns:
    plt.plot(df[time_column], df[column], label=column, linewidth=2)

# Customize the plot
plt.xlabel("Time", fontsize=12)
plt.ylabel("Agent Concentration", fontsize=12)
plt.title("Chemical Reaction Simulation - Agent Concentrations Over Time", fontsize=14)
plt.legend(bbox_to_anchor=(1.05, 1), loc="upper left", fontsize=20)
plt.grid(True, alpha=0.3)
plt.xlim(df[time_column].min(), df[time_column].max())  # Dynamic x-axis range

# Adjust layout to prevent legend cutoff
plt.tight_layout()

# Show the plot
# plt.show()

# Optional: Save the plot
plt.savefig("plot.png", dpi=300, bbox_inches="tight")