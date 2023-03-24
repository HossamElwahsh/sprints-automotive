# Monitoring and Control, Earned Value Management (EVM)
### Report this project status to the sponsor using EVM, assuming the project started 7 months ago

| TaskID  | Activity         | Predecessors   | Duration (month)           | BC (K$) | Progress   | AC (K$)      |
|---------|------------------|----------------|----------------------------|---------|------------|--------------|
| 1       | Preparation      | -              | 2                          | 600     | 100%       | 600          |
| 2       | Design           | 1              | 3                          | 1,200   | 100%       | 1,400        |
| 3       | Implementation   | 2              | 2                          | 400     | 50%        | 200          |
| 4       | Testing          | 2              | 3                          | 1,200   | 33.3%      | 500          |
| 5       | Deployment       | 4              | 3                          | 300     | 0%         | 0            |
| ------- | ---------------- | -------------- | **Total Planned Duration** | **BAC** | ---------- | **Total AC** |
|         |                  |                | 11 months                  | $3,700K |            | $2,700K      |



## Answer 👇

| Item | Desc.                                                          | Formula                        | Value   |
|------|----------------------------------------------------------------|--------------------------------|---------|
| BAC  | Budget at 100% completion                                      | Sum(BC)                        | $3,700K |
| PV   | Planned value to spend on what was planned to be completed     | Sum(BC * % Planned Completed ) | $3,000K |
| EV   | Earned value what you planned to spend on what's actually done | Sum(BC * % Actual Completed)   | $2,400K |
| AC   | Actual cost of completed work                                  | Sum(AC)                        | $2,700K |

### **1. By how much is it over/under budget = (CV)**
- Total planned duration considering predecessors = `11 months`
- Remaining time = `11 - 7 = 4 months`
- 7 months into project we should have completed: Tasks (1,2,3) and 66.7% of 4, 0% of 5
- PV = 600 + 1200 + 400 + (66.7% * 1200) = `$3,000K`
- EV = 600 + 1200 + (400 * 50%) + (1200 * 33.3%) + (300 * 0%) = `$2,400K`
- AC = 600 + 1400 + 200 + 500 = `$2,700K`
- CV = EV - AC = 2400 - 2700 = `$-300K`

  ### over budget by $300K
---

### **2. By how many days, is it ahead/behind the schedule**
- SV (Schedule variance)% = (EV - PV)/PV = (2400 - 3000)/3000 = `-20% behind schedule`
- Behind by = 11 mon * 20% = 2.2 mon = 66 days

  ### behind by 66 days assuming a month is 30 days, 
  _which are exactly in the two parallel tasks (3, 4) divided equally for each._ 

----
### **3. By the end of the project, by how much will it be over/under budget**
- Need to calculate VAC (variance at completion)
  - First calculate BAC, EAC
    - BAC = `$3,700K`
    - CPI = EV / AC = 2400 / 2700 = `0.89`
      - EAC = 2700 + ((3700 - 2400) / 0.89) = `$4,160K`
  - VAC = BAC - EAC = 3700 - 4160 = $ -460K

  ### Expected to be over budget by $460K at the end of the project
      

----

### Summary of calculated CV, SV, CPI, SPI, EAC

| Item | Description                                                | Formula                 | Result   |
|------|------------------------------------------------------------|-------------------------|----------|
| BAC  | Budget at completion, planned to spend at 100% project     | Sum(BC)                 | $ 3,700K |
| CV   | Cost Variance (how far over/under budget)                  | EV - AC                 | $  -300K |
| SV%  | Schedule Variance (how far ahead or behind schedule am I?) | (EV – PV)/PV            | -20%     |
| CPI  | Cost performance index (good over 1)                       | EV / AC                 | 0.89     |
| SPI  | Schedule performance index (good over 1)                   | EV / PV (Planned Value) | 0.8      |
| EAC  | Estimate at completion                                     | AC + ((BAC - EV) / CPI) | $ 4,160K |
| VAC  | Variance at completion of the total AC and expected cost   | BAC - EAC               | $  -460K |


