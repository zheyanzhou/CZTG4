with open('exampleB1.out', 'r') as f:
    start_counting = False
    cc_count = 0
    ec_count = 0
    ce_count = 0
    ee_count = 0
    se_count = 0
    for line in f:
        if line.strip() == "BEGIN":
            start_counting = True
        elif line.strip() == "STOP":
            start_counting = False
            with open('cc.txt', 'a') as cc_file:
                cc_file.write(str(cc_count) + '\n')
            with open('ec.txt', 'a') as ec_file:
                ec_file.write(str(ec_count) + '\n')
            with open('ce.txt', 'a') as ce_file:
                ce_file.write(str(ce_count) + '\n')
            with open('ee.txt', 'a') as ee_file:
                ee_file.write(str(ee_count) + '\n')
            with open('se.txt', 'a') as se_file:
                se_file.write(str(se_count) + '\n')
            cc_count = 0
            ec_count = 0
            ce_count = 0
            ee_count = 0
            se_count = 0
        elif start_counting:
            if "czt compt" in line:
                cc_count += 1
            elif "Envelope compt" in line:
                ec_count += 1
            elif "czt eIoni" in line:
                ce_count += 1
            elif "Envelope eIoni" in line:
                ee_count += 1
            elif "Parent ID = 1" in line:
                se_count += 1
